class LBox
{
  int bsize;
  int x;
  int y;
  int num;
  boolean selected;
  color textColor;
    
  
  LBox(int x1, int y1, int bs)
  {
    bsize = bs;
    x = x1;
    y = y1;
    num = -1;
    selected = false;
    textColor = color1;
  }
  
  void display()
  {
    if(selected)
    {
      fill(0,50);
      rect(x, y, bsize, bsize);
      noFill();
    }
    else
    {
      rect(x, y, bsize, bsize);
    }
    if(num > 0)
    {
      fill(textColor);
      text(num, x + bsize*6/25, y + bsize*22/25);
      noFill();
    }
  }
  
  boolean test(int mx, int my)
  {
    if(mx > x && mx < x + bsize && my > y && my < y + bsize)
    {
      selected = true;
      return true;
    }
    else
    {
      selected = false;
      return false;
    }
  }
}
