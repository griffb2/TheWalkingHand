#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	kinect.initSensor();
	//kinect.initIRStream(640,480);
	kinect.initColorStream(640,480,true);
	kinect.initDepthStream(640, 480, true);
	kinect.initSkeletonStream(true);

	//simple start
	kinect.start();
	ofEnableAlphaBlending(); //Kinect alpha channel is default 0;
	ofSetWindowShape(1600, 600);

	background.loadImage("background.png");

	ofDirectory dir;
	int nFiles = dir.listDir("walking");
	if(nFiles) {
		for(int i = 0; i < dir.numFiles(); i++){
			string filePath = dir.getPath(i);
			walking.push_back(ofImage());
			walking.back().loadImage(filePath);
		}
	}
	else cout << "couldn't open directory" << endl;

	walkingFrame = 0;
	headPosition = ofGetWidth()/2;
}

//--------------------------------------------------------------
void ofApp::update(){
	kinect.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	background.draw(0,0);

	//kinect.draw(640,0);
	//kinect.drawDepth(0,0);

	ofPushStyle();
	ofSetColor(255, 0, 0);
	ofSetLineWidth(3.0f);
	auto skeletons = kinect.getSkeletons();
	for(auto & skeleton : skeletons) {
		for(auto & bone : skeleton) {
			switch(bone.second.getTrackingState()) {
			case SkeletonBone::Inferred:
				ofSetColor(0, 0, 255);
				break;
			case SkeletonBone::Tracked:
				ofSetColor(0, 255, 0);
				break;
			case SkeletonBone::NotTracked:
				ofSetColor(255, 0, 0);
				break;
			}

			auto index = bone.second.getStartJoint();
			auto connectedTo = skeleton.find((_NUI_SKELETON_POSITION_INDEX) index);
			if (connectedTo != skeleton.end()) {
				ofLine(connectedTo->second.getScreenPosition(), bone.second.getScreenPosition());
			}

			if(kinect.isNewSkeleton()) {
				for( int i = 0; i < kinect.getSkeletons().size(); i++) 
				{
						// has a head? probably working ok then :)
					if(kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD) != kinect.getSkeletons().at(i).end())
					{
						// just get the first one
						SkeletonBone headBone = kinect.getSkeletons().at(i).find(NUI_SKELETON_POSITION_HEAD)->second;
						ofVec2f headScrenPosition( headBone.getScreenPosition().x, headBone.getScreenPosition().y);
						ofSetColor(ofColor::white);

						walkingFrame++;
						walkingFrame %= walking.size();
						//Moves the animation left or right depending on the user position
						if(headPosition > (headBone.getScreenPosition().x)) {//left
							walking[walkingFrame].draw(headBone.getScreenPosition().x, 200, -400, 350);
						}else
						walking[walkingFrame].draw(headBone.getScreenPosition().x, 200, 400, 350);


						headPosition = headBone.getScreenPosition().x;
							return;
					}
				}
			}


			ofCircle(bone.second.getScreenPosition(), 10.0f);
			
		}
	}
	ofPopStyle();
		//walking[0].draw(10,10, 100, 100);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
