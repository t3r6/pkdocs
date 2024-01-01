/*******************************************************
 PAINKILLER MPK
 (pseudo C syntax, 3dsmax default axes)
*******************************************************/

/***************************************************
  mesh definition
***************************************************/
for (meshcount) {
	/***********************************************
	  mesh entry
	***********************************************/
	(long) 0xDEAFBABE
	/***********************************************
	  mesh name
	***********************************************/
	(long) namelength
	(null_terminated_string) name
	/***********************************************
	  transform matrix
	***********************************************/
	16 x float // 1,0,0,0  0,1,0,0  0,0,1,0  0,0,0,1
	/***********************************************
	  vertices
	***********************************************/
	(long) numUVs // the value must be 1 or 2
	(long) num_vert	
	for (num_vert) {
		(float) X
		(float) Z
		(float) -Y
		if(numUVs==2){
			(float) 0
			(float) U_ch1
			(float) 1-V_ch1
			(float) U_ch2
			(float) 1-V_ch2
		}
		else{
			(float) X-normal
			(float) Z-normal
			(float) -Y-normal
			(float) U_ch1
			(float) 1-V_ch1
		}
	}
	/***********************************************
	  normals
	***********************************************/
	if(numUVs==2){
		(long) num_vert
		for (num_vert) {
			(float) X-normal
			(float) Z-normal
			(float) -Y-normal
		}			
	}
	else{
		(long) 0
	}
	/***********************************************
	  bounding box
	***********************************************/
	6 x float // x,z,y  x,z,y
	/***********************************************
	  faces
	***********************************************/
	(long) numfaces*3
	for (numfaces) {
		(short) vertex 0
		(short) vertex 2
		(short) vertex 1
	}
	/***********************************************
	  materials
	***********************************************/				
	(long) nummat
	for (nummat){
		(short) mat_offset	// by vertices
		(short) mat_size	// by faces
		/*******************************************
		  color map : uses 1st UV-channel
		*******************************************/
		(long) texnamelength
		(null_terminated_string) texname
		(float) Offset_u
		(float) Offset_v
		(float) Tiling_u
		(float) Tiling_v
		/*******************************************
		  light map : uses 2nd UV-channel
		*******************************************/
		(long) texnamelength
		(null_terminated_string) texname
		(float) Offset_u
		(float) Offset_v
		(float) Tiling_u
		(float) Tiling_v
		/*******************************************
		  blend map : uses 1st UV-channel
		*******************************************/
		(long) texnamelength
		(null_terminated_string) texname
		(float) Offset_u
		(float) Offset_v
		(float) Tiling_u
		(float) Tiling_v
		/*******************************************
		  alpha map : uses 2nd UV-channel
		*******************************************/
		(long) texnamelength
		(null_terminated_string) texname
		(float) Offset_u
		(float) Offset_v
		(float) Tiling_u
		(float) Tiling_v
	}
}
/***************************************************
  addressing
***************************************************/
for(meshcount){
	(long) meshoffset
}
(long) meshcount
/***************************************************
  end of file
***************************************************/
(long) 0xDEADBEEF