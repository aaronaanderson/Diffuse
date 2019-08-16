
#include "al/core.hpp"
//#include "al/core/sound/al_Ambisonics.hpp"
//#include "al/core/sound/al_AudioScene.hpp"
//#include <memory>
//#include "al/core/app/al_App.hpp"
//#include "al_ext/soundfile/al_SoundFileBuffered.hpp"

#include "al/util/imgui/al_Imgui.hpp"

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
float master = 0;
struct MyWindow : App
{
  
  gam::SoundFile soundFile;
  //SoundFileBuffered test;
  void onCreate() override {
    soundFile.openRead("data/microbialSurfaces.wav");
    initIMGUI();
    nav().pos(0, 0, 10);
    nav().setHome();
  }

  void onAnimate(double dt) override {

    beginIMGUI();
    ImGui::SliderFloat("Top", &top, 0.0f, 1.0f);
    ImGui::SliderFloat("Middle", &middle, 0.0f, 1.0f); 
    ImGui::SliderFloat("Bottom", &bottom, 0.0f, 1.0f);
    ImGui::SliderFloat("Front", &front, 0.0f, 1.0f); 
    ImGui::SliderFloat("Back", &back, 0.0f, 1.0f);
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

        for(int i = 0; i < io.channelsOut(); i++){
          //adjust gain for top, mid, bottom

          //adjust gain for front/back
          if(i < 7){//front bottom
            leftSample *= front;
            rightSample *= front;
            leftSample *= bottom;
            rightSample *= bottom;
            if(i < 4){
              io.out(i) = leftSample;
            }else{
              io.out(i) = rightSample;
            }
          }else if(i > 16 && i < 32){//front mid
            leftSample *= front;
            rightSample *= front;
            leftSample *= middle;
            rightSample *= middle;
            if(i < 24){
              io.out(i) = leftSample;
            }else{
              io.out(i) = rightSample;
            }
          }else if(i > 48 && i < 55){//front top
            leftSample *= front;
            rightSample *= front;
            leftSample *= top;
            rightSample *= top;
            if(i < 52){
              io.out(i) = leftSample;
            }else{
              io.out(i) = rightSample;
            }
          }
          if(i > 6 && i < 13){//back bottom
            leftSample *= back;
            rightSample *= back;
            leftSample *= bottom;
            rightSample *= bottom;
            if(i > 9){
              io.out(i) = leftSample;
            }else{
              io.out(i) = rightSample;
            }
          }else if(i > 31 && i < 47){//front mid
            leftSample *= front;
            rightSample *= front;
            leftSample *= middle;
            rightSample *= middle;
            if(i > 39){
              io.out(i) = leftSample;
            }else{
              io.out(i) = rightSample;
            }
          }else if(i > 54 && i < 61){//front top
            leftSample *= front;
            rightSample *= front;
            leftSample *= top;
            rightSample *= top;
            if(i > 57){
              io.out(i) = leftSample;
            }else{
              io.out(i) = rightSample;
            }
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
