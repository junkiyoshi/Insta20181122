#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofSetCircleResolution(30);
	
	this->noise_seed = 0;
}

//--------------------------------------------------------------
void ofApp::update() {

	int param = ofGetFrameNum() % 60;

	if (param < 45) {

		this->noise_seed += ofMap(param, 0, 45, 0.1, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	int size = 180;
	for (int x = size * 0.5; x < ofGetWidth(); x += size) {

		for (int y = size * 0.5 * 0.8; y < ofGetHeight(); y += size * 0.8) {

			this->draw_key(glm::vec2(x, y), size);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_key(glm::vec2 location, float len) {

	ofPushMatrix();
	ofTranslate(location);

	ofSetColor(39);
	ofDrawRectangle(glm::vec2(-len * 0.4, -len * 0.05), len * 0.8, len * 0.1);
	ofDrawCircle(glm::vec2(len * 0.25, 0), len * 0.2);

	float noise_value = 0;
	for (float x = -len * 0.4; x <= -len * 0.2; x += len * 0.05) {

		noise_value = ofNoise((location.x + x), location.y, this->noise_seed);
		ofDrawRectangle(glm::vec2(x, len * 0.05), len * 0.05, len * 0.3 * noise_value);
	}

	ofSetColor(ofGetBackground());
	ofDrawCircle(glm::vec2(len * 0.25, 0) + glm::vec2(len * 0.1 * cos((120 * noise_value - 60) * DEG_TO_RAD), len * 0.1 * sin((120 * noise_value - 60) * DEG_TO_RAD)), len * 0.05);

	ofPopMatrix();

}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}