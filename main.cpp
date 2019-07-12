
#include "al/core.hpp"
#include "al/core/sound/al_Ambisonics.hpp"
#include "al/core/sound/al_AudioScene.hpp"

#include <cmath>
#include <iostream>

using namespace al;

#define AUDIO_BLOCK_SIZE 256

struct MyWindow : App
{
  void onCreate() override {
      
  }

  void onDraw(Graphics& g) override {
    g.clear(0.5);
    g.pushMatrix();

    g.popMatrix();

  }

  void onKeyDown(const Keyboard& k) override {

  }

  void onSound(AudioIOData& io) override {

  }

};

int main(int argc, char* argv[]) {

  MyWindow win;
  win.initAudio(44100, AUDIO_BLOCK_SIZE, 2, 0);
  win.start();
    return 0;
}
