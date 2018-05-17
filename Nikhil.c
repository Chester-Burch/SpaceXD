//Declare any variables shared between functions here
float start[3];
float sps2[3];
float sps3[3];
float mystate[12];
float target[3];
int step;
float zinfo[4];
void init(){
	//This function is called once when your code is first loaded.

	//IMPORTANT: make sure to set any variables that need an initial value.
	//Do not assume variables will be set to 0 automatically!
	api.getMyZRState(mystate);
	start[0] = mystate[0];
	start[1] = mystate[1];
	start[2] = mystate[2];
	
	sps2[0] = -0.70;
	sps2[1] = 0.70;
	sps2[2] = 0.0;
	
	sps3[0] = 0.70;
	sps3[1] = 0.70;
	sps3[2] = 0.0;
	
	step = 0;
	
	game.dropSPS();
	api.setPositionTarget(sps2);
}

void loop(){
	//This function is called once per second.  Use it to control the satellite.
	api.getMyZRState(mystate);
	if (step == 0){
	    target[0] = -0.7;
	
	if (mystate[0] > target[0]){
	    api.setPositionTarget(sps2);
	}
	else{
	    game.dropSPS();
	    step++;
	}  
}
	else if (step == 1){
	    target[0] = 0.7;
	
	if (mystate[0] < target[0]){
	    api.setPositionTarget(sps3);
	}
	else{
	    game.dropSPS();
	    step++;
	} 
	}
	else if (step == 2){
	    game.getZone(zinfo);
	    if (mystate[0] >= 0.30 and mystate[0] <= 0.32 and mystate[1] >= 0.31 and mystate[1] <= 0.33){
	        DEBUG(("At large item"));
	        game.dockItem();
	        if (game.dockItem()){
	            DEBUG(("Got item"));
	        }
	        step ++;
	    }
	    
	    else{
	    sps3[0] = -1;
	    sps3[1] = -1;
	    sps3[2] = 0;
	    sps2[0] = 0.3;
	    sps2[1] = 0.3;
	    sps2[2] = 0;
	    game.getItemLoc(sps2,0);
	    api.setPositionTarget(sps2);
	    api.setAttitudeTarget(sps3);
	    }
	}
    else if (step == 3){
        if (game.dockItem()){
            game.getZone(zinfo);
            sps3[0] = zinfo[0];
            sps3[1] = zinfo[1];
            api.setPositionTarget(sps3);
            DEBUG(("%f", sps3[0]));
            if(mystate[0] == sps3[0]){
                game.dropItem();
                step ++;
            }
        }
        else{
            step = step - 1;
        }
        
    }
	else if (step == 4){
	    DEBUG(("Hope this works"));
	}
}
