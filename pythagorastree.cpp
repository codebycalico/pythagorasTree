#include "FPToolkit.c"

void recurse_tree(double p0[], double p1[], int iter, double angle, double f){
  if(iter == 0){
    return;
  }
  double delta_x, delta_y, nextp0[2], nextp1[2], p2[2], midpoint[2], p2_copy[2];
  // draw the square
  for(int i = 0; i < 3; i++){
    if(i == 2){
      nextp1[0] = p0[0];
      nextp1[1] = p0[1];
      nextp0[0] = p1[0];
      nextp0[1] = p1[1];
    }
    delta_x = p1[0] - p0[0];
    delta_y = p1[1] - p0[1];

    p2[0] = p1[0] - delta_y;
    p2[1] = p1[1] + delta_x;

    G_rgb(abs(0.2*p0[0] + 0.2*p0[1])/abs(p2[0]-p2[1]), 0.0, abs(0.6*p1[0] - 0.6*p1[1])/abs(p2[0] - p2[1]));
    G_line(p0[0],p0[1], p1[0], p1[1]);
    G_rgb(0.0, abs(0.2*p0[0] + 0.2*p0[1])/abs(p2[0]-p2[1]), abs(0.6*p1[0] - 0.6*p1[1])/abs(p2[0] - p2[1]));
    G_line(p1[0],p1[1], p2[0],p2[1]);

    p0[0] = p1[0];
    p0[1] = p1[1];
    p1[0] = p2[0];
    p1[1] = p2[1];
  }
  // creating the triangle
  double g = sqrt(f*(1-f));
  delta_x = nextp1[0] - nextp0[0];
  delta_y = nextp1[1] - nextp0[1];
  midpoint[0] = nextp0[0] + f*delta_x;
  midpoint[1] = nextp0[1] + f*delta_y;

  p2[0] = midpoint[0] - g*delta_y;
  p2[1] = midpoint[1] + g*delta_x;
  p2_copy[0] = midpoint[0] - g*delta_y;
  p2_copy[1] = midpoint[1] + g*delta_x;

  angle = (((M_PI)/180)*(45*iter));

  recurse_tree(nextp0, p2_copy, iter-1, angle, f);
  recurse_tree(p2, nextp1, iter-1, -angle, f);
}

int main(){
  printf("Click to choose the initial bottom right and left points.\n");

  int width = 700;
  int height = 700;
  G_init_graphics(width,height);

  G_rgb(0.0, 0.0, 0.0);
  G_clear();
  
  // choose points
  double p0[2], p1[2];
  G_wait_click(p0);
  G_wait_click(p1);

  double angle = ((M_PI)/180)*(45);
  double f = 0.70;
  int key = G_wait_key();

  while(key != (int)'q'){
    switch(key){
      case 97: //a
        recurse_tree(p0, p1, 2, angle, 0.70);
        key = G_wait_key();
        break;
      case 115: //s
        recurse_tree(p0, p1, 4, angle, 0.41);
        key = G_wait_key();
        break;
      case 100: //d
        recurse_tree(p0, p1, 7, angle, 0.27);
        key = G_wait_key();
        break;
      case 102: //f
        recurse_tree(p0, p1, 12, angle, 0.17);
        key = G_wait_key();
        break;
      case (int)'c': //c
        G_rgb(0.0, 0.0, 0.0);
        G_clear();
        key = G_wait_key();
        break;
    }
  }
  G_save_to_bmp_file("personal.bmp");
}