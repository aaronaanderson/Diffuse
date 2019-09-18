
#include "al/core.hpp"
//#include "al/core/sound/al_Ambisonics.hpp"
//#include "al/core/sound/al_AudioScene.hpp"
//#include <memory>
//#include "al/core/app/al_App.hpp"
//#include "al_ext/soundfile/al_SoundFileBuffered.hpp"

#include "al/util/imgui/al_Imgui.hpp"
#include "al/util/al_AlloSphereSpeakerLayout.hpp"
#include "Gamma/SoundFile.h"
#include <cmath>
#include <iostream>

using namespace al;

#define AUDIO_BLOCK_SIZE 256


float bottom = 0;
float middle = 0;
float top = 0;
float front = 0;
float back = 0;
float rotation = 0;
Vec2f rotationVector(cos(rotation), sin(rotation));
float focus = 1.0;
float master = 0;
float* bufferPointer;

SpeakerLayout speakerLayout;
struct MyWindow : App{
  
  gam::SoundFile soundFile;
  //SoundFileBuffered test;
  void onCreate() override {
    soundFile.openRead("data/microbialSurfaces.wav");
    initIMGUI();
    nav().pos(0, 0, 10);
    nav().setHome();

    speakerLayout = AlloSphereSpeakerLayout();
  }

  void onAnimate(double dt) override {

    beginIMGUI();
    ImGui::SliderFloat("Top", &top, 0.0f, 1.0f);
    ImGui::SliderFloat("Middle", &middle, 0.0f, 1.0f); 
    ImGui::SliderFloat("Bottom", &bottom, 0.0f, 1.0f);
    ImGui::SliderFloat("Front", &front, 0.0f, 1.0f); 
    ImGui::SliderFloat("Back", &back, 0.0f, 1.0f);
    ImGui::SliderFloat("Rotation", &rotation, 0.0f, 6.283185307179f);
    ImGui::SliderFloat("Focus", &focus, 1.0, 5.0);
    ImGui::SliderFloat("Master", &master, 0.0f, 1.0f);
    
    // don't nav if imgui's using inputs
    // ex) prevents camera rotation when mouse dragging scroll bar
    // nav is update after onAnimate and before onDraw.
    // so need to flag active/inactive here
    auto& io = ImGui::GetIO();
    bool using_gui = io.WantCaptureMouse | io.WantCaptureKeyboard
                                         | io.WantTextInput;
    navControl().active(!using_gui);
  }

  void onDraw(Graphics& g) override {
    g.clear(0.5);
    g.pushMatrix();
    g.popMatrix();
    endIMGUI();
  }

  void onKeyDown(const Keyboard& k) override {
    if(k.key() == ' '){
      soundFile.seek(0, 0);
    }
  }

  void onSound(AudioIOData& io) override {
    float buffer[AUDIO_BLOCK_SIZE*2];
    soundFile.read(buffer, AUDIO_BLOCK_SIZE);
    float* bufptr = buffer;
      
    while(io()) {
      float leftSample = *bufptr++;
      float rightSample = *bufptr++;

      leftSample *= master;
      rightSample *= master;
      rotationVector = Vec2f(cos(rotation), sin(rotation));
      
      for(int i = 0; i < io.channelsOut(); i++){//for every speaker.
        int whichLayer = speakerLayout.speakers()[i].group;

        //adjust samples for top, middle, and bottom
        switch (whichLayer){
          case 0://bottom
          leftSample *= bottom;
          rightSample *= bottom;
          break;

          case 1://middle
          leftSample *= middle;
          rightSample *= middle;
          break;

          case 2://top
          leftSample *= top;
          rightSample *= top;
          break;
        }

        //adjust for front and back  
        if(speakerLayout.speakers()[i].azimuth > 0.0){
          leftSample *= front;
          rightSample *= front;
        }else{
          leftSample *= back;
          rightSample *= back;
        }

        //distribute left and right input channel
        Vec2f speakerVector = Vec2f(cos(speakerLayout.speakers()[i].azimuth),sin(speakerLayout.speakers()[i].azimuth));
        float whichSide = rotationVector.dot(speakerVector);//negative for left, positive for right
        if(whichSide < 0.0f){
          leftSample *= pow(whichSide, focus);
          io.out(leftSample);
        }else{
          rightSample *= pow(-whichSide, focus);
          io.out(rightSample);
        }
      }
    }
  }
};

int main(int argc, char* argv[]) {

  MyWindow win;
  win.initAudio(44100, AUDIO_BLOCK_SIZE, 2, 0);
  win.start();
    return 0;
}
