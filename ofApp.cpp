#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int x = -300; x <= 300; x += 300) {

		for (int y = -300; y <= 300; y += 300) {

			ofPushMatrix();
			ofTranslate(x, y);
			
			ofRotateZ(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 3));
			ofRotateY(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 3));
			ofRotateX(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 3));

			ofMesh mesh;
			auto param = 30;
			glm::vec3 avg;
			float noise_value;

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec4(param, param, param, 0));
			vertices.push_back(glm::vec4(param, -param, -param, 0));
			vertices.push_back(glm::vec4(-param, param, -param, 0));
			vertices.push_back(glm::vec4(-param, -param, param, 0));

			avg = (vertices[0] + vertices[1] + vertices[2]) / 3;
			noise_value = ofNoise(glm::vec4(avg * 0.005 + glm::vec3(x, y, 0), ofGetFrameNum() * 0.02));
			noise_value = noise_value < 0.5 ? 0 : ofMap(noise_value, 0.5, 1, 0, 10);

			mesh.addVertex(vertices[0] + avg * noise_value);
			mesh.addVertex(vertices[1] + avg * noise_value);
			mesh.addVertex(vertices[2] + avg * noise_value);

			ofDrawLine(glm::vec3(), avg + avg * noise_value);

			avg = (vertices[0] + vertices[1] + vertices[3]) / 3;
			noise_value = ofNoise(glm::vec4(avg * 0.005 + glm::vec3(x, y, 0), ofGetFrameNum() * 0.02));
			noise_value = noise_value < 0.5 ? 0 : ofMap(noise_value, 0.5, 1, 0, 10);

			mesh.addVertex(vertices[0] + avg * noise_value);
			mesh.addVertex(vertices[1] + avg * noise_value);
			mesh.addVertex(vertices[3] + avg * noise_value);

			ofDrawLine(glm::vec3(), avg + avg * noise_value);

			avg = (vertices[0] + vertices[2] + vertices[3]) / 3;
			noise_value = ofNoise(glm::vec4(avg * 0.005 + glm::vec3(x, y, 0), ofGetFrameNum() * 0.02));
			noise_value = noise_value < 0.5 ? 0 : ofMap(noise_value, 0.5, 1, 0, 10);

			mesh.addVertex(vertices[0] + avg * noise_value);
			mesh.addVertex(vertices[2] + avg * noise_value);
			mesh.addVertex(vertices[3] + avg * noise_value);

			ofDrawLine(glm::vec3(), avg + avg * noise_value);

			avg = (vertices[1] + vertices[2] + vertices[3]) / 3;
			noise_value = ofNoise(glm::vec4(avg * 0.005 + glm::vec3(x, y, 0), ofGetFrameNum() * 0.02));
			noise_value = noise_value < 0.5 ? 0 : ofMap(noise_value, 0.5, 1, 0, 10);

			mesh.addVertex(vertices[1] + avg * noise_value);
			mesh.addVertex(vertices[2] + avg * noise_value);
			mesh.addVertex(vertices[3] + avg * noise_value);

			ofDrawLine(glm::vec3(), avg + avg * noise_value);

			ofSetColor(255);
			mesh.drawFaces();

			ofSetColor(0);
			mesh.drawWireframe();

			for (auto& vertex : mesh.getVertices()) {

				ofDrawSphere(vertex, 5);
			}
			ofDrawSphere(glm::vec3(), 5);

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}