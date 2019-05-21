// Copyright 2019 Hariharan Devarajan
//
// Created by keith on 5/21/19.
//

#ifndef SRC_BASKET_COMMUNICATION_RPC_LIB_TEMPL_CPP_
#define SRC_BASKET_COMMUNICATION_RPC_LIB_TEMPL_CPP_

template <typename F> void RPC::bind(std::string str, F func) {
  server->bind(str, func);
}
template <typename... Args>
RPCLIB_MSGPACK::object_handle RPC::call(uint16_t server_index,
                                        std::string const &func_name,
                                        Args... args) {
  AutoTrace trace = AutoTrace("RPC::call", server_index, func_name);
  int16_t port = server_port + server_index;
  /* Connect to Server */
  rpc::client client(server_list->at(server_index).c_str(), port);
  // client.set_timeout(5000);
  return client.call(func_name, std::forward<Args>(args)...);
}
template <typename... Args>
std::future<RPCLIB_MSGPACK::object_handle> RPC::async_call(
    uint16_t server_index, std::string const &func_name,
    Args... args) {
  AutoTrace trace = AutoTrace("RPC::async_call", server_index, func_name);
  int16_t port = server_port + server_index;
  /* Connect to Server */
  rpc::client client(server_list->at(server_index).c_str(), port);
  // client.set_timeout(5000);
  return client.async_call(func_name, std::forward<Args>(args)...);
}
#endif  // SRC_BASKET_COMMUNICATION_RPC_LIB_TEMPL_CPP_