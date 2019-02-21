#include<iostream>
#include<string>

using namespace std;

struct _USBCHECK_FLAGS
{
	unsigned char   DEVICE_DEFAULT_STATE       : 1;
	unsigned char   DEVICE_ADDRESS_STATE       : 1;
	unsigned char   DEVICE_CONFIGURATION_STATE : 1;
	unsigned char   DEVICE_INTERFACE_STATE     : 1;
	unsigned char   FOUR_RESERVED_BITS         : 8;
	unsigned char   RESET_BITS                 : 8;
} State_bits;

struct TestStruct
{
	unsigned int TEST_MAX	:1;
	unsigned int TEST_MIN	:1;

} TestItem;

int main(int argc, char* argv[])
{




}
