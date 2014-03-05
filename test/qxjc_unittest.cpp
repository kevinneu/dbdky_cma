#include "cma_client.h"

#include <utils/Logging.h>
#include <port/EventLoop.h>
#include <port/InetAddress.h>

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

using namespace dbdky;
using namespace dbdky::port;


#define SENDBUF_SIZE	94
const uint8_t sendbuf[SENDBUF_SIZE] = {0xa5, 0x5a,    //Header
	0x45, 0x00,//Data Length
	0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xff, 0xf0, 0xf8, //CMD_ID
	0x01,	//
	0x01,	//
	0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xff, 0xf0, 0xf8,
	0x21, 0x02, 0x13, 0x20,//time
	0x01, 0x02,		//alarm_flag
	0x78, 0x56, 0x34, 0x12,//Average_WindSpeed_10min
	0x34, 0x12,		//Average_WindDirection_10min
	0x78, 0x56, 0x34, 0x12,//Max_WindSpeed
	0x78, 0x56, 0x34, 0x12,//Extreme_WindSpeed
	0x78, 0x56, 0x34, 0x12,//Standard_WindSpeed
	0x78, 0x56, 0x34, 0x12,//Air_Temperature
	0x78, 0x56,		//Humidity
	0x78, 0x56, 0x34, 0x12,//Air_Pressure
	0x78, 0x56, 0x34, 0x12,//Precipitation
	0x78, 0x56, 0x34, 0x12,//Precipitation_Intensity
        0x56, 0x34,		//Radiation_Intensity
	0x78, 0x56, 0x34, 0x12,//Reserve1
	0x78, 0x56, 0x34, 0x12,//Reserve2

	0x0e,
	0x91
	
};

boost::shared_ptr<uint8_t> getTestData(int* length)
{
    *length = SENDBUF_SIZE;
    boost::shared_ptr<uint8_t> ret(new uint8_t[SENDBUF_SIZE]);
    for (int tmp = 0; tmp < SENDBUF_SIZE; tmp++)
    {
        memcpy(get_pointer(ret), sendbuf, SENDBUF_SIZE);
    } 

    return ret;
}


int main()
{
    EventLoop loop;
    InetAddress proxyAddr("127.0.0.1", 6001);
    dbdky::cma_client::cma_client client(&loop, proxyAddr, "cma_client");
    client.setGetSendDataCallback(boost::bind(getTestData, _1));
    client.start();
    loop.loop();
}
