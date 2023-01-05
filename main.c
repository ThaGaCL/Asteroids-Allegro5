#include "allegroDisplay.h"
#include "allegroUtil.h"
#include "asteroidsLib.h"

int main(){

    initAllegro();
    disp_init();
    sleep(2);
    disp_deinit();

    return 0;
}