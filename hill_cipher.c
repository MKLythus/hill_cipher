
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
void getinputc(char charray[], int sizelimit){
	size_t stringsize = 0;
	int i=0;
		
	fgets(charray, sizelimit, stdin);
	stringsize = strlen(charray)-1;
	if(charray[stringsize]== '\n'){
		charray[stringsize]='\0';
	}
	for (i=0; i<strlen(charray); i++){
	
		if( islower(charray[i])){
		
			charray[i] = toupper(charray[i]);
		
		}
	
	}


}

int keyinput(char charray[], int intray[][3]){
	int i=0;
	int j,k;
	for(j=0; j < 3; j++){
		for(k=0; k < 3; k++){			
			if(isalpha(charray[i])){
				intray[j][k] = ((charray[i]-38)%27);
			}
			else if(isspace(charray[i])){
				intray[j][k] = 26;
			
			}
			i++;
		}
		
	}
	/*for(j=0; j < 3; j++){
		for(k=0; k < 3; k++){			
			printf("%d", intray[j][k]);
		}
	}*/

	return 0;
}

int checknum(char charray[], int charsize){
	int i;
	for(i=0; i < charsize; i++){
//		printf("get this: %c\n", charray[i]);
		if(isalpha(charray[i]) ==0 && isspace(charray[i]) == 0){
		
			return 0;
		
		}
		
	}
	return 1;


}

void resetinput(char charray[], int charsize){
	int i;
	for(i=0; i < charsize; i++){
	
		charray[i] = '\0';
	
	}

}

int checkfordetmatrix(int i[][3]){
	int determinant = 0;
	determinant = (i[0][0]*i[1][1]*i[2][2]);
	determinant += (i[0][1]*i[1][2]*i[2][0]);
	determinant += (i[0][2]*i[1][0]*i[2][1]);
	determinant -= (i[2][0]*i[1][1]*i[0][2]);
	determinant -= (i[2][1]*i[1][2]*i[0][0]);
	determinant -= (i[2][2]*i[1][0]*i[0][1]);
	
	if(determinant == 0 || determinant%3 == 0){
		printf("Error: Determinant: %d \n", determinant);
		printf("Error: Determinant either has a common factor with modular base or is zero \n");
		return 0;
	}
	//printf("Determinant found: %d \n", determinant);
	return determinant;
}

int encrypt(int keymatrix[][3], char inputstring[], int charsize){
	int i=0;
	int j;
	int k;
	int total=0;
	int temporaryarray[3][1];
	size_t stringsize;
	
	//fgets(inputstring, charsize, stdin); //pangsalo
	fgets(inputstring, charsize, stdin);
	//printf("Augh: ");
//	puts(inputstring);
	stringsize = strlen(inputstring)-1;
	if(inputstring[stringsize]== '\n'){
		inputstring[stringsize]='\0';
	
	}
	while(strlen(inputstring)%3 != 0){
		//printf("ping");
		inputstring[strlen(inputstring)] = ' ';
		inputstring[strlen(inputstring)+1] = '\0';
	
	}
	for (i=0; i<strlen(inputstring); i++){
		if(isalpha(inputstring[i]) == 0 && isspace(inputstring[i]) == 0){
	
			printf("Error: Contains special characters! ");	
			return 0;
		}
		if( islower(inputstring[i])){
		
			inputstring[i] = toupper(inputstring[i]);
		
		}
	
	}
//	puts(inputstring);
	i=0;
	while(i < strlen(inputstring)){
		//printf("kangkong");
		for(j=0; j<3; j++){
		
			if(isalpha(inputstring[i])){
				temporaryarray[j][0] = ((inputstring[i]-38)%27);
			
			}
			if(isspace(inputstring[i])){
			
				temporaryarray[j][0] = 26;
			
			}
			
			i++;
			//printf("%d \n", temporaryarray[j][0]);
		}
	 	for(j=0; j<3; j++){
	 	
	 		for(k=0; k<3; k++){
	 	//		printf("%d %d\n", keymatrix[j][k], temporaryarray[k][0]);
	 			total +=(keymatrix[j][k]*temporaryarray[k][0]);
	 	//		printf("ponk");
	 		}
	 		if(total%27 <= 25){
	 			printf("%c", (total%27)+65);
	 		}
	 		else if( total%27 == 26){
	 			printf("%c", ' ');
	 		
	 		}
			total = 0;
	 	}
	 }
	printf("\n");
	return 1;
}
int modularmultinverse(int determinant){
	int x=0;
	int holder;
	while(determinant <0){
		determinant += 27;
	
	}
	for(x=1; x<27; x++){
		holder = (determinant*x)%27; 
		if(holder == 1){
			return x;
		
		
		}
	}
	printf("Sorry no result \n");
	return 0;
}
void matrixinvert(int matrixsrc[][3], int matrixddest[][3], int multiplicand){

	int i=0;
	int j=0;
	//printf("Multiplicand is %d\n", multiplicand);	
	matrixddest[0][0] = (matrixsrc[1][1]*matrixsrc[2][2]-matrixsrc[1][2]*matrixsrc[2][1]);
	matrixddest[0][1] = -1*(matrixsrc[0][1]*matrixsrc[2][2]-matrixsrc[0][2]*matrixsrc[2][1]);
	matrixddest[0][2] = (matrixsrc[1][2]*matrixsrc[0][1]-matrixsrc[1][1]*matrixsrc[0][2]);
	matrixddest[1][0] = -1*(matrixsrc[2][2]*matrixsrc[1][0]-matrixsrc[2][0]*matrixsrc[1][2]);
	matrixddest[1][1] = (matrixsrc[2][2]*matrixsrc[0][0]-matrixsrc[2][0]*matrixsrc[0][2]);
	matrixddest[1][2] = -1*(matrixsrc[1][2]*matrixsrc[0][0] - matrixsrc[1][0]*matrixsrc[0][2]);
	matrixddest[2][0] = (matrixsrc[2][1]*matrixsrc[1][0]-matrixsrc[2][0]*matrixsrc[1][1]);
	matrixddest[2][1] = -1*(matrixsrc[2][1]*matrixsrc[0][0]-matrixsrc[2][0]*matrixsrc[0][1]);
	matrixddest[2][2] = (matrixsrc[1][1]*matrixsrc[0][0]-matrixsrc[1][0]*matrixsrc[0][1]);
	
	/*for(i=0;i<3;i++){ 
		for(j=0;j<3;j++) {
			
			matrixddest[i][j] = (matrixsrc[(i+1)%3][(j+1)%3] * matrixsrc[(i+2)%3][(j+2)%3]) - (matrixsrc[(i+1)%3][(j+2)%3]*matrixsrc[(i+2)%3][(j+1)%3]); 
			
		}
	} */
	for(i=0;i<3;i++){ 
		for(j=0;j<3;j++){
			while( matrixddest[i][j] < 0){
			
				matrixddest[i][j]+=27;
			
			}
			matrixddest[i][j] = (matrixddest[i][j]*multiplicand);
		} 
	}
		
			
}

int main(){
	char tempbufferstr[3000];
	char foods[10] ;
	int tempkey[3][3];
	int foodint[3][3];
	char encryptthis[1000];
	int inversefood[3][3];
	//int determinant;
	//int stopprog = 0;
	//int tempmenu;
	
	do{
		printf("Please enter 9 characters (A to Z, a to z, space) for the key: \n");
		resetinput(tempbufferstr, 3000);
		getinputc(tempbufferstr, 3000); 
		if(strlen(tempbufferstr) > 9){
		
			printf("Error: String too long. Limit to 9 chars. \n");
			continue;
		}
		if(strlen(tempbufferstr) < 9 ){
			printf("Error: must enter 9 characters (A to Z, a to z, space)\n");
			continue;
			}
		if( checknum(tempbufferstr,9)==0){
			printf("Error: must not contain special chars or digits (A to Z, a to z, space: only) \n");
			continue;
		}
	
		
		
		strcpy(foods, tempbufferstr);
		
		
		//printf("%d\n",checknum(foods,9));

		keyinput(foods, tempkey);
	}
	while(strlen(tempbufferstr) < 9 || strlen(tempbufferstr) > 9 || (checknum(tempbufferstr,9) == 0) ||( checkfordetmatrix(tempkey) == 0));
	keyinput(foods, foodint);
//	puts(foods);
	printf("Press 1 to encrypt, 2 to decrypt( only one character!), anything else to exit!: \n");
	
	while(1){
		resetinput(tempbufferstr, 300);		
		getinputc(tempbufferstr, 300);
		if(strlen(tempbufferstr) > 1){
	
			printf("Please input only one character! \n");
				
		}
		else if(tempbufferstr[0] > '3' || tempbufferstr[0] < '0'){
			
			//printf("Error: input beyond range of 1 to 3 \n");
			return 0;
		}
		else if(tempbufferstr[0] == '3'){
		
			return 0;
		
		}
		else if(tempbufferstr[0] == '1'){
			do{
			
				printf("Enter phrase to encrypt: \n");
			
			}
			while(encrypt(foodint, encryptthis, 1024) == 0);
			return 1;
			}
		else if (tempbufferstr[0] == '2'){
			matrixinvert(foodint, inversefood, modularmultinverse(checkfordetmatrix(foodint)));
			do{
			
				printf("Enter phrase to decrypt: \n");
			
			
			}
			while(encrypt(inversefood, encryptthis,1024) == 0);		
			return 2;
		}
	}
	return 0;
}
