#include "cma_client.h"

#include <utils/Logging.h>
#include <port/EventLoop.h>
#include <port/InetAddress.h>

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

using namespace dbdky;
using namespace dbdky::port;

#define SENDBUF_SIZE 	76
const uint8_t sendbuf[SENDBUF_SIZE] = {0xa5, 0x5a,    //Header
	0x33, 0x00,//Data Length   21M0601JC00000001
	0x32,0x31,0x4d,0x30,0x36,0x30,0x31,0x4a,0x43,0x30,0x30, 0x30, 0x30, 0x30, 0x30, 0x30,0x31,//CMD_ID
	0x01,	//Frame_Type
	0x22,	//Packet_Type
        0x32,0x39,0x4d,0x30,0x30,0x30,0x30,0x30,0x30,0x31,0x32,0x31,0x38,0x35,0x33,0x33,0x32,
	0x4d, 0x21, 0x3f, 0x51,//time_stamp
	0x01, 0x00,				//Alerm_Flag
	0x02, 0x00, 0x00, 0x00,//Equal_IceThickness
	0x03, 0x00, 0x00, 0x00,//Tension
	0x04, 0x00, 0x00, 0x00,//Tension_Difference
	0x05, 0x00, 0x00, 0x00,//Windage_Yaw_Angle
	0x06, 0x00, 0x00, 0x00,//Deflection_Angle
	0x00, 0x00, 0x00, 0x00,//Reserve1
	0x00, 0x00, 0x00, 0x00,//Reserve2

	0xf6,
	0xc7
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

int main(int argc, char** argv)
{
    EventLoop loop;
    InetAddress proxyAddr("127.0.0.1", 6001);
    dbdky::cma_client::cma_client client(&loop, proxyAddr, "cma_client");
    client.setGetSendDataCallback(
        boost::bind(getTestData, _1));
    client.start();
    loop.loop();
    return 0;   
}
