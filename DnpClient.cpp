#include "DnpClient.h"

DnpClient::DnpClient(const std::string& name, const std::string& ip, uint16_t port, uint16_t masterAddress, uint16_t outstationAddress)
	: m_name(name)
	, m_ip(ip)
	, m_port(port)
	, m_masterAddress(masterAddress)
	, m_outstationAddress(outstationAddress)
	, m_connected(false)
	, m_channel(nullptr)
	, m_master(nullptr)
	, m_manager(nullptr)
{

}

DnpClient::~DnpClient()
{
	disconnect();
}


//Getters
//const at the end means that we can access the attributes but not change them
std::string DnpClient::getName() const
{
	return m_name;
}

std::string DnpClient::getIp() const
{
	return m_ip;
}

uint16_t DnpClient::getPort() const
{
	return m_port;
}

bool DnpClient::isConnected() const
{
	return m_connected;
}

//Disconnection method
void DnpClient::disconnect()
{
	if (m_master)
	{
		m_master->Disable();
		m_master = nullptr;  //clean previous address
	}

	if (m_channel)
	{
		m_channel->Shutdown();
		m_channel = nullptr;  //clean previous address
	}

	m_connected = false;
}

//Connection Method
void DnpClient::connect()
{
	//if it is connected already
	if (m_connected)
	{
		return;
	}

	//DNP3 Manager creates the channel
	//It cannot be a local attribute because it would be destroyed when the functions ends
	//so we created another private attribute
	m_manager = std::make_shared<opendnp3::DNP3Manager>(1, opendnp3::ConsoleLogger::Create());

	//level::NORMAL --> Just regular logging
	//ChannelRetry ---> Automatic reconnection if communication fails once
	//"0.0.0.0" ------> Any network interface
	m_channel = m_manager->AddTCPClient(m_name, opendnp3::levels::NORMAL, opendnp3::ChannelRetry::Default(), { opendnp3::IPEndpoint(m_ip, m_port) }, "0.0.0.0", nullptr);

	//MasterStackConfig ---> DNP3 Master configuration
	//ResponseTimeout -----> How long waits for a reply til determine timeout condition
	opendnp3::MasterStackConfig stackConfig;
	stackConfig.master.responseTimeout = opendnp3::TimeDuration::Seconds(5);
	stackConfig.link.LocalAddr = m_masterAddress;
	stackConfig.link.RemoteAddr = m_outstationAddress;

	m_master = m_channel->AddMaster(m_name, opendnp3::PrintingSOEHandler::Create(), opendnp3::DefaultMasterApplication::Create(), stackConfig);

	m_master->Enable();
	m_connected = true;
}