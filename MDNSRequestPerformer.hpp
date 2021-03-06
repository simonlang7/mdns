//
// Created by Simon Lang on 2019-02-14.
//

#pragma once


#include <ifaddrs.h>
#include <netinet/in.h>
#include <memory>
#include <unordered_map>

#include "mdnstypes.hpp"

namespace mdns
{

class MDNSRequestPerformer
{
public:
    /**
     * Creates an mDNS request performer for all available interfaces
     * @return
     */
    static std::shared_ptr<MDNSRequestPerformer> create();

    /**
     * Constructs an mDNS request performer. Use create() instead.
     * @param addrs addresses obtained by getifaddrs
     */
    explicit MDNSRequestPerformer(ifaddrs* addrs);
    virtual ~MDNSRequestPerformer();

    /**
     * @return A vector of pairs containing the interface name as the first element
     *         and the interface address as the second element
     */
    std::vector<std::pair<std::string, std::string>> listIPv4Interfaces();

    void closeSocket(std::string& interfaceAddress);
    void closeAllSockets();

    Status mDNSDiscoverySend(std::string& interfaceAddress);
    Reply mDNSDiscoveryReceive(std::string& interfaceAddress);

    Status mDNSQuerySend(std::string& interfaceAddress);
    Reply mDNSQueryReceive(std::string& interfaceAddress);

private:
    ifaddrs* addrs;
    std::vector<std::pair<std::string, std::string>> ipv4interfaces;
    std::unordered_map<std::string, in_addr> ipv4addresses;
    std::unordered_map<std::string, int> sockets;
    void* buffer;
    size_t capacity = 2048;

    Status openSocket(std::string& interfaceAddress);

};

} // namespace mdns

