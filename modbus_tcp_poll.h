typedef struct modbus_poll_tx_msg{
	unsigned char msg_id[2];         // any value
	unsigned char identification[2]; // set zero;
	unsigned char len[2]; // left message length after current member 
	unsigned char slave_id;
	unsigned char function;
	unsigned char start_addr[2];
	unsigned char xfer_len[2]; // length of bytes to get from this xfer
	                           // wanted data if function 05
	unsigned char data[4];
	unsigned char data1[256]; // cut data into two pieces in case of 64 bit alignment
}modbus_poll_tx_msg;

