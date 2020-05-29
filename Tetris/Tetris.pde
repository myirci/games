Engine engine;
Renderer renderer;
void setup()
{
  size(720, 640);
  frameRate(5);
  engine = new Engine(); 
  renderer = new Renderer(engine);
}

void draw()
{
  if(engine.run())
  {
    renderer.display(); 
  }
}

void keyPressed() 
{
  if(key == CODED)
  {
    switch(keyCode)
    {
      case LEFT:
        engine.decrement_x(true);
        break;
      case RIGHT:
        engine.increment_x(true);
        break;
      case DOWN:
        engine.soft_drop(true);
        break;
      case UP:
        engine.rotate_cw(true);
        break;
      case SHIFT:
        engine.hold_release_tetrimino();
      case CONTROL:
      // rotate counter clockwise
      break;
    }
  }
  
  switch(key)
  {
    case 'n':
    case 'N':
      engine.new_game();
      break;
    case 'c':
    case 'C':
      engine.hold_release_tetrimino();
      break;
    case 'd':
    case 'D':
      engine.debug();
      break;
    case 'p':
    case 'P':
      engine.pause_the_current_game();
      break;
    case 'x':
    case 'X':
      engine.rotate_cw(true);
      break;
    case 'z':
    case 'Z':
      // Rotate counter clockwise
      break;
    case 32:
      engine.hard_drop();
      break;
  }
}

void keyReleased()
{
  if(key == CODED)
  {
    switch(keyCode)
    {
      case DOWN:
        engine.soft_drop(false);
        break;
      case LEFT:
        engine.decrement_x(false);
        break;
      case RIGHT:
        engine.increment_x(false);
        break;
      case UP:
        engine.rotate_cw(false);
    }
  }
  else
  {
    switch(key)
    {
      case 'x':
      case 'X':
        engine.rotate_cw(false);
        break;
    }
  }
}
