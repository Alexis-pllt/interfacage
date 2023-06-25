#include <mbed.h>
#include <threadLvgl.h>
#include "demos/lv_demos.h"
#include <cstdio>

ThreadLvgl threadLvgl(30);

#include "MPU6050.h"
MPU6050 mpu6050;
// git
int main()
{
  int cpt = 231;
  int cpt1 = 231;
  int cpt2 = 231;
  int cpt3 = 0;
  int vitesse = 0;
  char chaine[20];  
  int delay1 = 153;
  int delay2 = 307;
  int score = 0;

  mpu6050.resetMPU6050();                        // Reset registers to default in preparation for device calibration
  mpu6050.calibrateMPU6050(gyroBias, accelBias); // Calibrate gyro and accelerometers, load biases in bias registers
  mpu6050.initMPU6050();
  printf("MPU6050 initialized for active data mode....\n\r"); // Initialize device for active mode read of acclerometer, gyroscope, and temperature

  threadLvgl.lock();
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x00a2e8), LV_PART_MAIN);
  lv_obj_clear_flag(lv_scr_act(),LV_OBJ_FLAG_SCROLLABLE);


  /*Create a white label, set its text and align it to the center*/

  LV_IMG_DECLARE(htuyaux);
  lv_obj_t *imghtuyaux = lv_img_create(lv_scr_act());
  lv_img_set_src(imghtuyaux, &htuyaux);
  lv_obj_align(imghtuyaux, LV_ALIGN_CENTER, -230, -200);

  LV_IMG_DECLARE(btuyaux);
  lv_obj_t *imgbtuyaux = lv_img_create(lv_scr_act());
  lv_img_set_src(imgbtuyaux, &btuyaux);
  lv_obj_align(imgbtuyaux, LV_ALIGN_CENTER, -230, 200);

  LV_IMG_DECLARE(htuyaux1);
  lv_obj_t *imghtuyaux1 = lv_img_create(lv_scr_act());
  lv_img_set_src(imghtuyaux1, &htuyaux);
  lv_obj_align(imghtuyaux1, LV_ALIGN_CENTER, -400, -100);

  LV_IMG_DECLARE(btuyaux1);
  lv_obj_t *imgbtuyaux1 = lv_img_create(lv_scr_act());
  lv_img_set_src(imgbtuyaux1, &btuyaux);
  lv_obj_align(imgbtuyaux1, LV_ALIGN_CENTER, -400, 300);

  LV_IMG_DECLARE(htuyaux2);
  lv_obj_t *imghtuyaux2 = lv_img_create(lv_scr_act());
  lv_img_set_src(imghtuyaux2, &htuyaux);
  lv_obj_align(imghtuyaux2, LV_ALIGN_CENTER, -400, -250);

  LV_IMG_DECLARE(btuyaux2);
  lv_obj_t *imgbtuyaux2 = lv_img_create(lv_scr_act());
  lv_img_set_src(imgbtuyaux2, &btuyaux);
  lv_obj_align(imgbtuyaux2, LV_ALIGN_CENTER, -400, 150);

  LV_IMG_DECLARE(flappy);
  lv_obj_t *imgflappy = lv_img_create(lv_scr_act());
  lv_img_set_src(imgflappy, &flappy);
  lv_obj_align(imgflappy, LV_ALIGN_CENTER, -150, 0);


  lv_obj_t * label = lv_label_create(lv_scr_act());
  lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_CENTER, -220, -125);

  lv_obj_t * label2 = lv_label_create(lv_scr_act());
  lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
  lv_obj_align(label2, LV_ALIGN_CENTER, -0, -0);
  lv_label_set_text(label2, "");


  threadLvgl.unlock();
  int decalage = 0;
  int dpl;

  while (1)
  {
    // If data ready bit set, all data registers have new data
    if (mpu6050.readByte(MPU6050_ADDRESS, INT_STATUS) & 0x01)
    {                                    // check if data ready interrupt
      mpu6050.readAccelData(accelCount); // Read the x/y/z adc values
      mpu6050.getAres();

      // Now we'll calculate the accleration value into actual g's
      ax = (float)accelCount[0] * aRes; // get actual g value, this depends on scale being set
      ay = (float)accelCount[1] * aRes;
      az = (float)accelCount[2] * aRes;

      dpl = ay * 1000;

      if (dpl > 50)
      {
        decalage = decalage - ay * 10;
        if (decalage < -125)
        {
          decalage = -125;
        }
      }
      else if (dpl < 50)
      {
        decalage = decalage - ay * 10;
        if (decalage > 125)
        {
          decalage = 125;
        }
      }
      else
      {
        decalage = decalage;
      }

 
    vitesse ++;
    delay1--;
    delay2--;
    if (vitesse < 0)
    {
    lv_label_set_text(label2, "GAME OVER");

    }
    if (vitesse < 1500 && vitesse >= 0)
    {
      cpt--;
      if (delay1 < 0)
      {
        cpt1--;
      }
      if (delay2 < 0)
      {
        cpt2--;
      }
      if (cpt < -230)
      {
        cpt = 231;
      }
      if (cpt1 < -230)
      {
        cpt1 = 231;
      }
      if (cpt2 < -230)
      {
        cpt2 = 231;
      }
    }
    if (vitesse > 1500 && vitesse < 3000)
    {
      cpt --;
      cpt1 --;
      cpt2 --;
      if (vitesse % 10 == 0) {
        cpt --;
        cpt1 --;
        cpt2 --;
    }
      if (cpt < -230)
      {
        cpt = 231;
      }
      if (cpt1 < -230)
      {
        cpt1 = 231;
      }
      if (cpt2 < -230)
      {
        cpt2 = 231;
      }
    }
    if (vitesse > 3000 && vitesse < 4500)
    {
      cpt --;
      cpt1 --;
      cpt2 --;
      if (vitesse % 5 == 0) {
        cpt --;
        cpt1 --;
        cpt2 --;
    }
      if (cpt < -230)
      {
        cpt = 231;
      }
      if (cpt1 < -230)
      {
        cpt1 = 231;
      }
      if (cpt2 < -230)
      {
        cpt2 = 231;
      }
    }
    if (vitesse > 4500 && vitesse < 6000)
    {
      cpt --;
      cpt1 --;
      cpt2 --;
      if (vitesse % 2 == 0) {
        cpt --;
        cpt1 --;
        cpt2 --;
    }
      if (cpt < -230)
      {
        cpt = 231;
      }
      if (cpt1 < -230)
      {
        cpt1 = 231;
      }
      if (cpt2 < -230)
      {
        cpt2 = 231;
      }
    }
    if (vitesse > 6000 )
    {
      cpt  = cpt  - 2;
      cpt1 = cpt1 - 2;
      cpt2 = cpt2 - 2;
     
      if (cpt < -230)
      {
        cpt = 231;
      }
      if (cpt1 < -230)
      {
        cpt1 = 231;
      }
      if (cpt2 < -230)
      {
        cpt2 = 231;
      }
    }

    if ((cpt > -150) & (cpt < -120))
    {
      
      if ((cpt == -130))
      {
        score ++;
      }

      if ((decalage > -15) || (decalage < -57))
      {
        decalage = 125;
        vitesse = -1000;
      }
    }
    if ((cpt1 > -150) && (cpt1 < -120))
    {
      
    if ((cpt1 == -130))
      {
        score ++;
      }

            if ((decalage < 40) || (decalage > 88))
      {
        decalage = 125;
        vitesse = -1000;
      }
    }

    if ((cpt2 > -150) && (cpt2 < -120))
    {
      
      if ((cpt2 == -130) )
      {
        score ++;
      }

      if ((decalage > -62) || (decalage < -108))
      {
        decalage = 125;
        vitesse = -1000;
      }
    }


    
    sprintf(chaine, "%d", score);


    
    threadLvgl.lock();
    lv_obj_set_y(imgflappy, decalage);
    lv_obj_set_x(imghtuyaux, cpt);
    lv_obj_set_x(imgbtuyaux, cpt);
    lv_obj_set_x(imghtuyaux1, cpt1);
    lv_obj_set_x(imgbtuyaux1, cpt1);
    lv_obj_set_x(imghtuyaux2, cpt2);
    lv_obj_set_x(imgbtuyaux2, cpt2);
    lv_label_set_text(label, chaine);

    threadLvgl.unlock();

    ThisThread::sleep_for(10ms);
    printf("test");
  }
}
}