//NK -->
#define MAX_ENCOUNTER_TYPES			32 // was 16, was 8 stock
int ENCOUNTERS_QUANTITY = 0;
// NK <-- 

// Encounters types
#define ENCOUNTER_TYPE_MERCHANT0			0
#define ENCOUNTER_TYPE_MERCHANT1			1
#define ENCOUNTER_TYPE_MERCHANT2			2
#define ENCOUNTER_TYPE_PATROL				3
#define ENCOUNTER_TYPE_FLEET				4
#define ENCOUNTER_TYPE_CORSAR				5
#define ENCOUNTER_TYPE_PIRATE				6
// kobuk's new encounter types
#define ENCOUNTER_TYPE_PUNITIVE_SQUADRON	7
#define ENCOUNTER_TYPE_LMERCHANT0			8
#define ENCOUNTER_TYPE_LMERCHANT1			9
#define ENCOUNTER_TYPE_LMERCHANT2			10
#define ENCOUNTER_TYPE_LPATROL				11
#define ENCOUNTER_TYPE_LFLEET				12
#define ENCOUNTER_TYPE_LCORSAR				13
#define ENCOUNTER_TYPE_LPIRATE				14
#define ENCOUNTER_TYPE_LPUNITIVE_SQUADRON	15
#define ENCOUNTER_TYPE_SM 					16		// Silent Marry			Mirsaneli add
// <-- 

// Encounter type
#define ENCOUNTER_TRADE				0
#define ENCOUNTER_WAR				1

object EncountersTypes[MAX_ENCOUNTER_TYPES];
