

Systick::Systick()
{
	SYSTICK_IntCmd(ENABLE);
	SYSTICK_InternalInit(5);
	SYSTICK_Cmd(ENABLE);
	
}
