/* -*-C++-*- 

   "$Id: FSocket.H,v 1.1 2000/05/14 02:41:20 jamespalmer Exp $"
   
   Copyright 1997 GARRET.
   Copyright 1999-2000 by the Flek development team.
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA.
   
   Please report all bugs and problems to "flek-devel@sourceforge.net".

*/

// FSocket was adapted from K.A. Knizhnik's very nice SAL library.

#ifndef __FSOCKET_H__
#define __FSOCKET_H__

#include <time.h>

#define DEFAULT_CONNECT_MAX_ATTEMPTS 100
#define DEFAULT_RECONNECT_TIMEOUT    1  // seconds
#define DEFAULT_LISTEN_QUEUE_SIZE    5
#define LINGER_TIME                  10 // seconds
#define WAIT_FOREVER                 ((time_t)-1)

#if defined(_WIN32) && !defined(__CYGWIN__)
typedef HANDLE descriptor_t; 
#else
typedef int descriptor_t; 
#endif

/**
 * Abstract socket interface
 */
class FSocket { 
 public: 
  virtual int read(void* buf, size_t min_size, size_t max_size,
		   time_t timeout = WAIT_FOREVER) = 0;
  virtual int read(void* buf, size_t size) = 0;
  virtual int write(void const* buf, size_t size) = 0;
  
  virtual int is_ok() = 0; 
  virtual void get_error_text(char* buf, size_t buf_size) = 0;

  /**
   * This method is called by server to accept client connection
   */
  virtual FSocket* accept() = 0;
  
  /**
   * Cancel accept operation and close socket
   */
  virtual int cancel_accept() = 0;
  
  /**
   * Shutdown socket: prohibite write and read operations on socket
   */
  virtual int shutdown() = 0;
  
  /**
   * Close socket
   */
  virtual int close() = 0;
  
  /**
   * Create client socket connected to local or global server socket
   */
  enum socket_domain { 
    sock_any_domain,   // domain is chosen automatically
    sock_local_domain, // local domain (i.e. Unix domain socket) 
    sock_global_domain // global domain (i.e. INET sockets) 
  };
  
  static FSocket* connect(char const* address, 
			   socket_domain domain = sock_any_domain, 
			   int max_attempts = DEFAULT_CONNECT_MAX_ATTEMPTS,
			   time_t timeout = DEFAULT_RECONNECT_TIMEOUT);
  
  /**
   * Create local domain socket
   */
  static FSocket* create_local(char const* address,
				int listen_queue_size = 
				DEFAULT_LISTEN_QUEUE_SIZE);
  
  /**
   * Create global domain socket 
   */
  static FSocket* create_global(char const* address,
				 int listen_queue_size = 
				 DEFAULT_LISTEN_QUEUE_SIZE);
  
  virtual ~FSocket() {} 
  FSocket() { state = ss_close; }
  
 protected:
  enum { ss_open, ss_shutdown, ss_close } state;
};

// 
// Return current host name + identifier of current process
//
extern char const* get_process_name(); 

#endif

