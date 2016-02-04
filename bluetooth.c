// Turn on bluetooth and make it visible

task main()
{
	setBluetoothOn();
	wait1Msec(1000);
	setBluetoothVisibility(true);
	wait1Msec(1000);
	setDefaultPIN("1234");
}
