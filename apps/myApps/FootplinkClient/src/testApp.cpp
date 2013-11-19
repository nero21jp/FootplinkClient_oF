#include "testApp.h"
#include <fstream>
#include <string>
#include <iostream>
#include <time.h>
#include <stdint.h>
#include <math.h>
#define PI 3.14159265
#define SettingFilePath "CSVPath.conf"
//--------------------------------------------------------------

string FilePath;

void FilePathSetting()
{
	std::ifstream ifs(SettingFilePath);

	if(ifs.fail()) {
		std::cerr << "Setting File do not exist.\n";
		exit(0);
	}
	getline(ifs,FilePath);
}

void pop(int Que[5])
{
	int i;
	double buff[5];
	for(i=0;i < 4;i++)
		{
			buff[i] = Que[i];
		}
	for(i=0;i < 4;i++)
		{
			Que[i+1] = buff[i];
		}
	Que[0] = 0;
}

void test(double buff[4])
{
	std::ifstream ifs(FilePath.c_str());
	std::string str;

	if(ifs.fail()) {
		std::cerr << "CSV File do not exist.\n";
		exit(0);
	}
	int nowline = 0;
		while(getline(ifs, str)) {
		char a[30],x[20],y[20];
		char o[20],p[30];
		char hour[20],second[20],minite[20],minsecond[20];
		char year[20],month[20],day[20];
		char* ends;
		double from2k;
		nowline++;
		if(nowline == buff[3])
		{
			sscanf(str.data(),"%[^,],%[^,],%[^,]", &a, &x, &y);
			sscanf(a,"%s %s", &o, &p);
			char s1[] = "/";
			strcpy(year, strtok(o, s1));strcpy(month, strtok(NULL, s1));strcpy(day, strtok(NULL, s1));

			char s2[] = ":";  /* 空白+ハイフン+ピリオド */
			strcpy(hour, strtok(p, s2));strcpy(minite, strtok(NULL, s2));strcpy(second, strtok(NULL, s2));strcpy(minsecond, strtok(NULL, s2));
			buff[0] = strtod( minsecond, &ends);
			buff[1] = strtod(x, &ends);
			buff[2] = strtod(y, &ends);
			buff[3] = nowline;
			ifs.close();
			return;
		}
		else{}
		}
}

bool NowPositionFirstGetter(double buff[4])
{
    //Console::WriteLine(L"Hello World");
	time_t now = time(NULL);
	struct tm *pnow = localtime(&now);
	std::cout << asctime(pnow) << std::endl;

	std::ifstream ifs(FilePath.c_str());
	std::string str;

	if(ifs.fail()) {
		std::cerr << FilePath.c_str() << " CSV File do not exist.\n";
		while(1){}
		exit(0);
	}
	int nowline = 0;
	while(getline(ifs, str)) {
		char a[30],x[20],y[20];
		char o[20],p[30];
		char hour[20],second[20],minite[20],minsecond[20];
		char year[20],month[20],day[20];
		char *ends;
		double from2k;

		nowline++;
		sscanf(str.data(),"%[^,],%[^,],%[^,]", &a, &x, &y);
		sscanf(a,"%s %s", &o, &p);
		char s1[] = "/";
		strcpy(year, strtok(o, s1));strcpy(month, strtok(NULL, s1));strcpy(day, strtok(NULL, s1));
		char s2[] = ":";  /* 空白+ハイフン+ピリオド */
		strcpy(hour, strtok(p, s2));strcpy(minite, strtok(NULL, s2));strcpy(second, strtok(NULL, s2));strcpy(minsecond, strtok(NULL, s2));
		
		struct tm y2k;
		time_t at2k;
		y2k.tm_sec = atoi(second);       /* 秒 */
		y2k.tm_min = atoi(minite);       /* 分 */
		y2k.tm_hour = atoi(hour);      /* 時 */
		y2k.tm_mday = atoi(day);      /* 日 */
		y2k.tm_mon = atoi(month) - 1;       /* 月 ( 1月＝0 ) */
		y2k.tm_year = atoi(year) - 1900;    /* 西暦年 - 1900 */
		y2k.tm_isdst = -1;
		at2k = mktime(&y2k);

		from2k = difftime(now, at2k);
		std::cout << from2k << std::endl;
		int timerag = 0;
		if(from2k >= 30)//30秒以上ラグがあるデータは読み飛ばす
		{
			continue;
		}
		while(timerag < 30)//誤差29秒以内で最も近いデータを出力する
		{
			if(from2k == timerag)
			{
				//一番近いやつかどうか判定
				/*
				if(atoi(minsecond) < genminsec)
				{
					buff[0] = atoi(minsecond);
					buff[1] = atoi(x);
					buff[2] = atoi(y);
				}
				if(atoi(minsecond) < genminsec)
				{
					if( (genminsec-atoi(minsecond)) < (buff[0]-genminsec) )
					{
						buff[0] = atoi(minsecond);
						buff[1] = atoi(x);
						buff[2] = atoi(y);
					}
					else{}
					return; //判定終了
				}
				*/
				/*
				buff[0] = atoi(minsecond);
				buff[1] = atoi(x);
				buff[2] = atoi(y);
				buff[3] = nowline;
				*/
				buff[0] = strtod( minsecond, &ends);
				buff[1] = strtod(x, &ends);
				buff[2] = strtod(y, &ends);
				buff[3] = nowline;
				ifs.close();
				return true;
			}
			else
			{
				timerag++;
			}
		}
	}
	std::cerr << "Not exist data within 30sec in CSV file.\n";
	buff[0] = 0;
	buff[1] = 0;
	buff[2] = 0;
	buff[3] = 1;
	//buff[3] = nowline-1;
	ifs.close();
	return false;
}

bool NowPositionGetter(double buff[4])
{
	std::ifstream ifs(FilePath.c_str());
	std::string str;

	if(ifs.fail()) {
		std::cerr << "CSV File do not exist.\n";
		exit(0);
	}
	int nowline = 0;
	while(true) {
		char a[30],x[20],y[20];
		char o[20],p[30];
		char hour[20],second[20],minite[20],minsecond[20];
		char year[20],month[20],day[20];
		char *ends;
		double from2k;
		getline(ifs, str);
		if(ifs.eof()==true)
		{
			return false;
		}
		nowline++;
		if(nowline == buff[3])
		{
			sscanf(str.data(),"%[^,],%[^,],%[^,]", &a, &x, &y);
			sscanf(a,"%s %s", &o, &p);
			char s1[] = "/";
			strcpy(year, strtok(o, s1));strcpy(month, strtok(NULL, s1));strcpy(day, strtok(NULL, s1));
			char s2[] = ":";  /* 空白+ハイフン+ピリオド */
			strcpy(hour, strtok(p, s2));strcpy(minite, strtok(NULL, s2));strcpy(second, strtok(NULL, s2));strcpy(minsecond, strtok(NULL, s2));
			buff[0] = strtod( minsecond, &ends);
			buff[1] = strtod(x, &ends);
			buff[2] = strtod(y, &ends);
			buff[3] = nowline;
			return true;
		}
		else{}
	}
	return false;
}

void testApp::setup(){
	FilePathSetting();
	// window size, frame rate/s
	//Wwidth = 2000;
	//Wheight = 1500;
	ofToggleFullscreen();
	Wwidth = ofGetScreenWidth();
	Wheight = ofGetScreenHeight();
	
	//Frate = 2;
	//ofSetWindowShape(Wwidth,Wheight);
	//ofSetFrameRate(Frate);
	// white background
	ofBackground(0, 0, 0);
	//初期値
	ImageRatioLX = 0.4;
	ImageRatioRX = 0.5;
	ImageRatioLY = 0.95;
	ImageRatioRY = 1;
	LorR = 0;
	Counter = 0;
	//画像データの読み込み
	FootLeftImage.loadImage("images/big01_left_w.png");
	FootRightImage.loadImage("images/big01_right_w.png");

	//その他
	ofSetVerticalSync(true);
	
	int num = 1000;
	p.assign(num, demoParticle());
	currentMode = PARTICLE_MODE_REPEL;

	//デフォルトモード
	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 

	resetParticles();
	BallOn = 0;

	NowlineIs = 0;

	PublicBuff[0] = 0;
	PublicBuff[1] = 0;
	PublicBuff[2] = 0;
	PublicBuff[3] = 0;

	//NowPositionFirstGetter(PublicBuff);
	//test(PublicBuff);
	NowPositionFirstGetter(PublicBuff);
	NowlineIs = PublicBuff[3];

	LorR_B = 1;

	font1.loadFont("GOTHIC.ttf", 20);
}

//--------------------------------------------------------------
void testApp::resetParticles(){
	//these are the attraction points used in the forth demo 
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( ofPoint( ofMap(i, 0, 4, 100, ofGetScreenWidth()-100) , ofRandom(100, ofGetScreenHeight()-100) ) );
	}
	
	attractPointsWithMovement = attractPoints;
	
	for(int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].setAttractPoints(&attractPointsWithMovement);
		p[i].reset();
	}
}

//--------------------------------------------------------------
void testApp::update(){
	Counter += 1;
	if(BallOn == 1){
		for(int i = 0; i < p.size(); i++){
			p[i].setMode(currentMode);
			p[i].update(ImageX,ImageY);
		}
		//lets add a bit of movement to the attract points
		for(int i = 0; i < attractPointsWithMovement.size(); i++){
			attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
			attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
		}
	}

	//PublicBuffを更新
	if((Counter%5)==0)
	{
		if((Counter%10)==0)
		{
			ImageRatioX = (PublicBuff[1] + 2)/4;
			ImageRatioY = PublicBuff[2]/4;
			ImageX = (int)(ImageRatioX * Wwidth);
			ImageY = (int)(ImageRatioY * Wheight);
			LorR_B = 0;
			pop(LXque);
			pop(LYque);
			pop(LDegQue);
		}
		else
		{
			ImageRatioX = (PublicBuff[1] + 2)/4;
			ImageRatioY = PublicBuff[2]/4;
			ImageX = (int)(ImageRatioX * Wwidth);
			ImageY = (int)(ImageRatioY * Wheight);
			LorR_B = 1;
			pop(RXque);
			pop(RYque);
			pop(RDegQue);
		}
	}

	if(FileEndFlag == true)
	{
	}
	else
	{
		NowlineIs++;
	}
	PublicBuff[3] = NowlineIs;
	FileEndFlag = !NowPositionGetter(PublicBuff);
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

	if(BallOn == 1){
		void ofDisableAlphaBlending();
		for(int i = 0; i < p.size(); i++){
			p[i].draw();
		}
	
		ofSetColor(190);
		if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
			for(int i = 0; i < attractPoints.size(); i++){
				ofNoFill();
				ofCircle(attractPointsWithMovement[i], 10);
				ofFill();
				ofCircle(attractPointsWithMovement[i], 4);
			}
		}
	}

	ofSetColor(230);	
	//ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
	ofSetColor( 255, 255, 255);
	myImage.draw(50, 50, 50, 50);
	//red circle
	ofEnableAlphaBlending();

	ofSetColor(255, 255, 255);
	if(LorR_B == 0)
	{
		ImageLX = ImageX - 50;
		ImageLY = ImageY;
		//FootLeftImage.draw(ImageLX, ImageLY, 50, 100);
		LXque[0] = ImageLX;
		LYque[0] = ImageLY;
		double rad = 180 - atan2((double)(LXque[0] - LXque[1]),(double)(LYque[0] - LYque[1]))*180/PI;
		LDegQue[0] = (int)rad;
	}
	else
	{
		ImageRX = ImageX + 50;
		ImageRY = ImageY;
		//FootRightImage.draw(ImageRX, ImageRY, 50, 100);
		RXque[0] = ImageRX;
		RYque[0] = ImageRY;
		double rad = 180 - atan2((double)(RXque[0] - RXque[1]),(double)(RYque[0]-RYque[1]))*180/PI;
		RDegQue[0] = (int)rad;
	}
	int s;
	for(s = 4;s >= 0;s--)
	{
		ofSetColor(255-(40*s),255-(40*s),255-(40*s));

		ofPushMatrix();
		ofTranslate(LXque[s],LYque[s],0);
		ofRotateZ(LDegQue[s]);
		FootLeftImage.draw(0, 0, 50, 100);
		ofPopMatrix();

		ofPushMatrix();
		ofTranslate(RXque[s],RYque[s],0);
		ofRotateZ(RDegQue[s]);
		FootRightImage.draw(0, 0, 50, 100);
		ofPopMatrix();
	}
	
	//string CommandHelp = "Key Command\nkey1->from the data now\nkey2->from the head of the recorded data\nkey5->ball\nkey6->no ball\nc->clear all data\n";
	//ofDrawBitmapString(CommandHelp, (int)(0.8*Wwidth), (int)(0.8*Wheight));
	font1.drawString("Key Command\n1->from the data now\n2->from the head of the recorded data\n5->ball\n6->no ball\nc->clear all data\n", 100, 200);
	string FlagText= ofToString(FileEndFlag);
	ofDrawBitmapString(FlagText, (int)(0.5*Wwidth), (int)(0.1*Wheight));
	//以下デバッグ用出力
	/*
	string rt = ofToString(PublicBuff[1],2) + ":" + ofToString(PublicBuff[2],2) + ":" + ofToString(PublicBuff[3]);
	ofDrawBitmapString(rt, 100, 200);

	string rt2 = ofToString(ImageX) + ":" + ofToString(ImageY) + ":" + ofToString(NowlineIs) + ":" + ofToString(Counter) + ":" + ofToString(LorR_B) + " " +ofToString(LDegQue[0]);
	ofDrawBitmapString(rt2, 200, 400);

	string rt3 = ofToString(LXque[0]) + ":" + ofToString(LXque[1]) + ":" + ofToString(LXque[2]);
	ofDrawBitmapString(rt3, 200, 800);
	*/
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	/*
	if( key == '1'){
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 		
	}
	if( key == '2'){
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse"; 				
	}
	if( key == '3'){
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS: hold 'f' to disable force"; 						
	}
	if( key == '4'){
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation"; 						
		resetParticles();
	}	
		
	if( key == ' ' ){
		resetParticles();
	}
	*/
	if(key == '1'){
		NowPositionFirstGetter(PublicBuff);
		NowlineIs = PublicBuff[3];
		LorR_B = 1;
	}
	if(key == '2'){
		PublicBuff[3] = 1;
		test(PublicBuff);
		NowlineIs = PublicBuff[3];
		LorR_B = 1;
	}
	if( key == '5' ){
		resetParticles();
		BallOn = 1;
	}
	if( key == '6'){
		resetParticles();
		BallOn = 0;
	}
	if( key == 'c'){
		std::ofstream ofs( FilePath, std::ios::out | std::ios::trunc );
		ofs.close();
		NowPositionFirstGetter(PublicBuff);
		NowlineIs = PublicBuff[3];
		LorR_B = 1;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}