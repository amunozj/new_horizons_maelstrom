
void CreateJungles(int iIslandIndex)
{
	if(CheckAttribute(&Islands[iIslandIndex],"jungle.texture") && CheckAttribute(&Islands[iIslandIndex],"jungle.patch")) 
	{
		//CreateGrass("resource\models\islands\"+ Islands[iIslandIndex].id +"\"+ Islands[iIslandIndex].id + "_jungle.grs", "Grass\grass.tga", 10.0, 10.0,1000.0, 100.0,2000.0, 0.6);
		float fJungleScale = 10.0;
		if( CheckAttribute(&Islands[iIslandIndex],"jungle.scale") ) {
			fJungleScale = stf(Islands[iIslandIndex].jungle.scale);
		}
		CreateGrass("resource/models/islands/"+ Islands[iIslandIndex].id +"/"+ Islands[iIslandIndex].jungle.patch + ".grs", "Grass/"+Islands[iIslandIndex].jungle.texture+".tga", fJungleScale, 20.0, 200.0, 100.0, 800.0, 0.6);
	}
}