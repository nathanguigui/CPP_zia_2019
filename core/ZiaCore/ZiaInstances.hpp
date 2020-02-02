//
// Created by guigui on 2/2/20.
//

#ifndef CPP_ZIA_2019_ZIAINSTANCES_HPP
#define CPP_ZIA_2019_ZIAINSTANCES_HPP

struct ZiaInstances {
    boost::asio::io_service ioService;
    boost::asio::io_context ioContext;
    ITcpServer *tcpServer;
};

#endif //CPP_ZIA_2019_ZIAINSTANCES_HPP
