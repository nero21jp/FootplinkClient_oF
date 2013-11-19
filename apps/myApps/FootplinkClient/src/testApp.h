#pragma once

#include "ofMain.h"
#include "demoParticle.h"

class testApp : public ofBaseApp{
	private:
		ofTrueTypeFont font1,font2;
	public:
		//void NowPositionFirstGetter(double buff[4]);
		void setup();
		void update();
		void draw();
		void resetParticles();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		int Wwidth, Wheight, Frate, ImageRX, ImageRY, ImageLX, ImageLY, ImageX, ImageY;
		int LXque[5],LYque[5],RXque[5],RYque[5],LDegQue[5],RDegQue[5];
		int NowlineIs;
		int Counter;
		bool LorR,LorR_A,LorR_B,FileEndFlag;
		bool BallOn;
		double ImageRatioLX, ImageRatioRX, ImageRatioLY, ImageRatioRY;
		double ImageRatioX, ImageRatioY;
		double rad;
		float posX, posY;
		double PublicBuff[4];
		
		particleMode currentMode;
		string currentModeStr; 

		vector <demoParticle> p;
		vector <ofPoint> attractPoints;
		vector <ofPoint> attractPointsWithMovement;

		ofImage FootLeftImage;
		ofImage grabbedFootLeftImage;
		ofImage FootRightImage;
		ofImage grabbedFootRightImage;

		ofImage myImage;
};
