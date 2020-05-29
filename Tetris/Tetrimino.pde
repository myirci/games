import java.util.Arrays;

public enum TetriminoType 
{
  T(1), 
  L(2),
  J(3),
  I(4),
  S(5),
  Z(6),
  O(7);
  
  private final int val;
  
  private TetriminoType(int v)
  {
    this.val = v;
  }
  
  public int get_val()
  {
    return val;
  }
}

public class Tetrimino
{
  public TetriminoType type;
  public int[] data;
  public int h; // height in north orientation
  public int w; // width in north orientation
  
  public Tetrimino(TetriminoType t) 
  {
    type = t;
    data = new int[16];
    Arrays.fill(data, 0);
    h = 2;
    w = 3;
    switch(type)
    {
      case T:
        data[4] = 1;
        data[5] = 1;
        data[6] = 1;
        data[9] = 1;
        break;
      case L:
        data[4] = 2;
        data[5] = 2;
        data[6] = 2;
        data[10] = 2;
        break;
      case J:
        data[4] = 3;
        data[5] = 3;
        data[6] = 3;
        data[8] = 3;
        break;
      case I:
        h = 1;
        w = 4;
        data[8] = 4;
        data[9] = 4;
        data[10] = 4;
        data[11] = 4;
        break;
      case S:
        data[4] = 5;
        data[5] = 5;
        data[9] = 5;
        data[10] = 5;
        break;
      case Z:
        data[5] = 6;
        data[6] = 6;
        data[8] = 6;
        data[9] = 6;
        break;
      case O:
        w = 2;
        data[5] = 7;
        data[6] = 7;
        data[9] = 7;
        data[10] =7;
        break;
    }
  }
}
