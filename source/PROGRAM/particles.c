object Particles;
object ParticlesXPS;
#event_handler("CreateParticleSystemPost", "CreateParticleSystemEvent"); // NK 04-09-21 add createpartsys event

void InitParticles()
{
	Particles.windpower = 1.0;
	Particles.winddirection.x = frnd();
	Particles.winddirection.z = frnd();
	ParticlesXPS.windpower = 1.0;
	ParticlesXPS.winddirection.x = frnd();
	ParticlesXPS.winddirection.z = frnd();
	if (!CreateParticleEntity() || !CreateParticleEntityXPS())
	{
		Trace("Can't create 'particles' class");
	}
}

void PauseParticles(bool bPause)
{
	if (!CreateParticleEntity()) return;
	SendMessage(&Particles, "ll", PS_PAUSEALL, bPause);
}

void DeleteParticles()
{
	SendMessage(&Particles,"l", PS_CLEARALL);
	Particles.winddirection.x = frnd();
	Particles.winddirection.z = frnd();
}

void DeleteParticleSystem(int id)
{
	SendMessage(&Particles,"ll",PS_DELETE,id);
}


int CreateParticleSystem(string name,float x,float y,float z,
		float ax,float ay,float az,int lifetime)
{
	int pid;
	if (!CreateParticleEntity()) return 0;
	pid = SendMessage(&Particles,"lsffffffl",PS_CREATE,name,x,y,z,ax,ay,az,lifetime);
	return pid;
}

int CreateParticleSystemXPS(string name,float x,float y,float z,
		float ax,float ay,float az,int lifetime)
{
	int pid;
	if (!CreateParticleEntityXPS()) return 0;
	pid = SendMessage(&ParticlesXPS,"lsffffffl",PS_CREATE,name,x,y,z,ax,ay,az,lifetime);
	return pid;
}

// NK createparsys event 04-09-21 -->
void CreateParticleSystemEvent()
{
	string name = GetEventData();
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();
	float ax = GetEventData();
	float ay = GetEventData();
	float az = GetEventData();
	int lifetime = GetEventData();
	CreateParticleSystem(name, x, y, z, ax, ay, az, lifetime);
}
// NK <--

bool CreateParticleEntity()
{
	if(IsEntity(&Particles) == false)
	{
		if (CreateEntity(&Particles,"particleslegacy") == false) return false;
		LayerAddObject("realize",Particles,65536);
		LayerAddObject("execute",Particles,0);
		LayerAddObject(SEA_REALIZE,Particles,65536);
		LayerAddObject(SEA_EXECUTE,Particles,0);
	}
	return true;
}

bool CreateParticleEntityXPS()
{
	if(IsEntity(&ParticlesXPS) == false)
	{
		if (CreateEntity(&ParticlesXPS,"particles") == false) return false;
		LayerAddObject("realize",ParticlesXPS,65536);
		LayerAddObject("execute",ParticlesXPS,0);
		LayerAddObject(SEA_REALIZE,ParticlesXPS,65536);
		LayerAddObject(SEA_EXECUTE,ParticlesXPS,0);
	}
	return true;
}

int CreateParticleSystemX(string name,float x,float y,float z,
		float ax,float ay,float az,int lifetime)
{
	int pid;
	if (!CreateParticleEntity()) return false;
	pid = SendMessage(&Particles,"lsffffffl",PS_CREATEX,name,x,y,z,ax,ay,az,lifetime);
	return pid;
}

int CreateBlast(float x,float y,float z)
{
	int iRes;
	object blast;
	iRes = CreateEntity(&blast,"blast");
	SendMessage(&blast,"lfff",LM_SETPOINT,x,y,z);
	LayerAddObject("realize",blast,65536);	// was 3 - Mirsaneli: prevents fog rendering over particles which made them look white
	LayerAddObject(SEA_REALIZE,blast,65536);	// was 3 - Mirsaneli: prevents fog rendering over particles which made them look white
	return iRes;
}

int CreateBlastX(float x,float y,float z,float ax,float ay,float az)
{
	int iRes;
	object blast;
	iRes = CreateEntity(&blast,"blast");
	SendMessage(&blast,"lffffff",LM_SETPOINTANDANGLES,x,y,z,ax,ay,az);
	LayerAddObject("realize",blast,65536);	// was 3 - Mirsaneli: prevents fog rendering over particles which made them look white
	LayerAddObject(SEA_REALIZE,blast,65536);	// was 3 - Mirsaneli: prevents fog rendering over particles which made them look white
	return iRes;
}

// MM, modified blast for solid shot impacts, flying planks removed.
// TIH --> This function crashes the game because the "flying planks removed" portion was done improperly.
// As a result, we are bypassing this function and using the stock one above to insure proper particles.
int CreateBlastM(float x,float y,float z)
{
	return CreateBlast( x, y, z); // bypass this function and use stock above
	/*
	int iRes;
	object blast;
	iRes = CreateEntity(&blast,"blast");
	SendMessage(&blast,"lfff",LM_SETPOINT,x,y,z);
	LayerAddObject("realize",blast,3);
	return iRes;
	*/
}
// TIH <--
