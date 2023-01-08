#include "allegroDisplay.h"
#include "allegroUtil.h"
#include "asteroidsLib.h"
#include "allegroSprites.h"
#include "allegroFx.h"
#include "allegroKeyboard.h"
#include "allegroAudio.h"

int main(){

    initAllegro();
    disp_init();
    sleep(2);
    disp_deinit();

    return 0;
}