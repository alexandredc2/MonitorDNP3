#pragma once

#include <string>  //save the IEDs names and IPs.
#include <memory>  //for managing pointers with no need to manual delete
#include <opendnp3/DNP3Manager.h>  //threads managing, communication channels
#include <opendnp3/channel/IChannel.h>  //TCP Connection
#include <opendnp3/master/IMaster.h>  //DNP3 master, polling, data receive
#include <opendnp3/master/DefaultMasterApplication.h>  //callback master, link event
#include <opendnp3/master/ISOEHandler.h>  //Sequence of Events Handler (data read from ieds)
#include <opendnp3/ConsoleLogger.h>
#include <opendnp3/master/PrintingSOEHandler.h>


//Each new dnp3 connection will create an object of this class.
class DnpClient
{
public:
	DnpClient(const std::string& name, const std::string& ip, uint16_t port, uint16_t masterAddress, uint16_t outstationAddress);
	~DnpClient();

	void connect();
	void disconnect();
	bool isConnected() const;
	std::string getName() const;
	std::string getIp() const;
	uint16_t getPort() const;

private:
	std::string m_name;  //ied name
	std::string m_ip;  //ied ip
	uint16_t	m_port;  //tcp port
	uint16_t	m_masterAddress;  //my pc dnp address (client)
	uint16_t	m_outstationAddress;  //ied dnp address (server)
	bool		m_connected;  //determine if the IED is connected or not

	std::shared_ptr<opendnp3::IChannel> m_channel;
	std::shared_ptr<opendnp3::IMaster> m_master;
	std::shared_ptr<opendnp3::DNP3Manager> m_manager;
};
