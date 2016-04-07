

int calc_rock(int rock_type, int preCost)
{
	int costTotal;
	int winSig;
	int winTotal;
	int costCnt;

	if(rock_type == 1){
		winSig = 10;
	}
	if(rock_type == 2){
		winSig = 15;
	}
	if(rock_type == 3){
		winSig = 30;
	}
	if(rock_type == 4){
		winSig = 250;
	}

	costCnt = 1;
	winTotal = winSig * costCnt;
	preCost += costCnt * 5;

	while(winTotal < preCost + 10){
		costCnt++;
		preCost += 5;
		winTotal = winSig * costCnt;
	}
	

	return costCnt;	
}

void play_rock(int rock_type, int count)
{
	int i;
	int preCost = 0;
	int rockCnt;
	int totWin;

	for(i=0; i<count; i++){
		rockCnt = calc_rock(rock_type, preCost);
		preCost += rockCnt * 5;

	}
	if(rock_type == 1){
		totWin = 10 * rockCnt;
	}
	if(rock_type == 2){
		totWin = 15 * rockCnt;
	}
	if(rock_type == 3){
		totWin = 30 * rockCnt;
	}
	if(rock_type == 4){
		totWin = 250 * rockCnt;
	}
	printf("need rock count %d\n", rockCnt);
	printf("total cost %d\n", preCost);
	printf("total win %d\n", totWin);

}
