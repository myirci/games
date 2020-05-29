import java.util.Random;
import java.util.Queue;
import java.util.LinkedList;

public enum EngineStatus
{
  GameRun,
  GamePause,
  BlockOut,
  LockOut,
  NoGame,
  Exit
}

public enum TetriminoStatus
{
  InPlay,
  LockDown,
  Animate
}

public class Engine
{
  public int[][] matrix;
  public int[][] minos;
  private final int mh = 23;  // matrix height
  private final int mw = 10;  // matrix width
  
  public Tetrimino ct;  // current tetrimino  
  private int ctx;      // current tetrimino bottom left-x
  private int cty;      // current tetrimino bottom left-y
  
  public Tetrimino ht;       // hold tetrimino
  public TetriminoType htt;  // hold tetrimino type
  
  public int level;
  public int score;
  public int line_clears;
  public int goal;
  public int num_tetrises;
  public int num_tetriminos;
  
  private int gtd;   // game tick duration 
  private int gts;   // game tick start
  private int lds;   // lock down start
  private int ldd;   // lock down duration
  private int as;    // animation start
  private int ad;    // animation duration
  private int ldc;   // lock down count since last hold
  
  private int cxs;  // change of x start
  private int cxd;  // change of x duration
  private int cws;  // clock-wise rotation start
  private int rod;  // rotation duration
  
  private boolean hd; // hard drop
  private boolean ix; // increment x
  private boolean dx; // decrement x
  private boolean rcw; // rotate cw
  private boolean rht; // release hold tetrimino
  
  private EngineStatus est;          
  private TetriminoStatus tst;
  public Queue<Tetrimino> bag;
  
  Random random;
  
  public Engine()
  {
    est = EngineStatus.NoGame;    
    matrix = new int[mh][mw];
    minos = new int[4][2];
    bag = new LinkedList<Tetrimino>();
    random = new Random();
    score = 0;
    level = 1;
    line_clears = 0;
    num_tetrises = 0;
    num_tetriminos = 0;
    goal= 10;
    gtd = (int)(1000 * Math.pow(0.8 - (level - 1) * 0.007, level - 1));
    ldd = 500;
    ad = 500;
    cxd = 45;
    rod = 70;
    ctx = 0;
    cty = 0;
    gts = 0;
    ldc = 0;
    hd = false;
    ix = false;
    dx = false;
    rcw = false;
    rht = false;
  }
 
  public void new_game()
  {
    if(est == EngineStatus.NoGame || est == EngineStatus.BlockOut || est == EngineStatus.LockOut)
    {
      init_new_game();
    }
    else 
    {
      // pause the current game
      if (est != EngineStatus.GamePause)
      {
        pause_the_current_game();
      }
      
      // ask for confirmation  
    }      
  }
  
  public void debug()
  {
    System.out.println(est);

    System.out.println("Content of bag");
    //access via new for-loop
    for(Tetrimino t : bag) 
    {
      System.out.println(t.type.name());
    }
    
    print_matrix();
  }
  
  private void print_matrix()
  {
    for(int i = mh-1; i >= 0; i--)
    {
      for(int j = 0; j < mw; j++)
      {
        System.out.print(matrix[i][j] + " ");
      }
      System.out.println();
    }
  }
  
  private boolean is_valid(int x, int y)
  {
    for(int i = 0; i < 16; i++)
    {
      if(ct.data[i] == 0)
      {
        continue;
      }
      
      int x1 = x + i % 4;
      int y1 = y + i / 4;
      if(x1 < 0 || x1 > 9 || y1 < 0 || y1 > 23 || matrix[y1][x1] != 0)
      {
        return false;
      }
    }
    return true;
  }
  
  private boolean is_valid(int[] temp)
  {
    for(int i = 0; i < 16; i++)
    {
      if(temp[i] == 0)
      {
        continue;
      }
      
      int x1 = ctx + i % 4;
      int y1 = cty + i / 4;
      if(x1 < 0 || x1 > 9 || y1 < 0 || y1 > 23 || (matrix[y1][x1] != 0 && matrix[y1][x1] < 10))
      {
        return false;
      }
    }
    return true;
  }
  
  private void update_minos_from_current_position(boolean new_tetrimino)
  {    
    int j = 0; 
    for(int i = 0; i < 16; i++)
    { 
      if(ct.data[i] == 0)
      {
        continue;
      }
      minos[j][0] = ctx + i % 4;
      minos[j][1] = cty + i / 4;
     
      if(new_tetrimino && matrix[minos[j][1]][minos[j][0]] != 0)
      {
        // Block out
        est = EngineStatus.BlockOut;
        return;
      }      
      j++;
    }
    
    if(minos[0][1] >= mh && minos[1][1] >= mh && minos[2][1] >= mh && minos[3][1] >= mh)
    {
      est = EngineStatus.LockOut;
    } 
  }
  
  private int update_matrix_from_current_position()
  {    
    int row_count = 0;
    for(int i = 0; i < 16; i++)
    { 
      if(ct.data[i] == 0)
      {
        continue;
      }
      matrix[cty + i / 4][ctx + i % 4] = ct.data[i];
    }
    
    for(int i = 0; i < mh; i++)
    {
      boolean row_complete = true;
      for(int j = 0; j < mw; j++)
      {
        if(matrix[i][j] == 0)
        {
          row_complete = false;
          break;
        }
      }
      if(row_complete)
      {
        row_count++;
        for(int j = 0; j < mw; j++)
        {
          matrix[i][j] = 8;
        }
      }
    }
    
    return row_count;
  }
  
  private void remove_rows()
  {
    int mback[] = new int[mh];
    int rcount = 0;
    for(int i = 0; i < mh; i++)
    {
      if(matrix[i][0] == 8)
      {
        rcount++;
        mback[i] = 0; 
      }
      else
      {
        mback[i] = rcount;
      }
    }
    
    for(int i = 0; i < mh; i++)
    {
      if(mback[i] != 0)
      {
        for(int j = 0; j < mw; j++)
        {
          matrix[i-mback[i]][j] = matrix[i][j]; 
        }    
      }  
    }
  }
  
  public void soft_drop(boolean enable)
  {
    if(est == EngineStatus.GameRun  && tst == TetriminoStatus.InPlay)
    {
      if(enable)
      {
        gtd /= 20.0;
      }
      else
      {
        gtd = (int)(1000 * Math.pow(0.8 - (level - 1) * 0.007, level - 1));
      }
    }
  }
  
  public void hard_drop()
  {
    if(est == EngineStatus.GameRun  && tst == TetriminoStatus.InPlay)
    {
        gtd = 1;
        hd = true;
    }
  }
  
  public void increment_x(boolean inc)
  {
    if(est == EngineStatus.GameRun)
    {
      ix = inc;
      if(inc)
      {
        cxs = millis();
      }
    }
  }
  
  public void decrement_x(boolean dec)
  {
    if(est == EngineStatus.GameRun)
    {
      dx = dec;
      if(dec)
      {
        cxs = millis();
      }
    }
  }
  
  public void rotate_cw(boolean r)
  {
    if(est == EngineStatus.GameRun)
    {
      rcw = r;
      if(r)
      {
        cws = millis();
      }
    }
  }
  
  public void hold_release_tetrimino()
  {
    if(est == EngineStatus.GameRun && tst == TetriminoStatus.InPlay && ldc > 0)
    {
      if(ht != null)
      {
        rht = true;
      }
      
      ht = new Tetrimino(ct.type);
      get_new_tetrimino();
      htt = ht.type;
      ldc = 0;
    }
  }
  
  private boolean lock_piece()
  {
    boolean updated = false;
    int num_removed_rows = update_matrix_from_current_position(); 
    if(num_removed_rows != 0)
    {
      // start animation
      as = millis();
      tst = TetriminoStatus.Animate;
      updated = true;
      switch(num_removed_rows)
      {
        case 1:
          score += level*100;
          break;
        case 2:
          score += level*300;
          break;
        case 3:
          score += level*500;
          break;
        case 4:
          score += level*800;
          num_tetrises++;
          break;
      }
      line_clears += num_removed_rows;
      goal -= num_removed_rows;
      if(goal <= 0)
      {
        level++;
        goal = 10;
      }
    }
    else
    {
      get_new_tetrimino();
    }
    ldc++;
    return updated;
  }
  
  public boolean run()
  {
    boolean updated = false;
    
    // check the game status
    if(est != EngineStatus.GameRun)
    {
      if(est == EngineStatus.BlockOut)
      {
        frameRate(5);
        // println("Game Over - Blockout");
      }
      else if(est == EngineStatus.LockOut)
      {
        frameRate(5);
        // println("Game Over - Lockout");
      }
      return updated;
    }
    
    if(tst == TetriminoStatus.InPlay)
    {
      // check for game tick 
      if(millis() - gts >= gtd)
      {
        gts = millis();
        if(is_valid(ctx, cty-1))
        {
          cty--;
          updated = true;
        }
        else if(!hd)
        {
          // start lock down
          lds = millis();
          tst = TetriminoStatus.LockDown;
        }
        else
        {
          if(lock_piece())
          {
            updated = true;
          }
          hd = false;
        }
      }
    }
     
    if(tst == TetriminoStatus.InPlay || tst == TetriminoStatus.LockDown)
    {
      if(ix && millis() - cxs > cxd)
      {
        if(is_valid(ctx + 1, cty))
        {
          ctx++;
          updated = true;
        }
        cxs = millis();
      }
      else if(dx && millis() - cxs > cxd)
      {
        if(is_valid(ctx - 1, cty))
        {
          ctx--;
          updated = true;
        }
        cxs = millis();
      }
      else if(rcw && millis() - cws > rod)
      {
        int[] temp = new int[16];
        for(int i = 0; i < 16; i++)
        {
          temp[i] = ct.data[3 - i / 4 +  4 * (i % 4)]; 
        }
        if(is_valid(temp))
        {
          ct.data = temp;
          updated = true;
        }
        cws = millis();
      }
    }
    
    if(updated)
    {
      update_minos_from_current_position(false);
    }
    
    if(tst == TetriminoStatus.LockDown)
    {
      if(is_valid(ctx, cty-1))
      {
        tst = TetriminoStatus.InPlay;
      }
      else
      {
        if(millis() - lds >= ldd)
        {
          if(lock_piece())
          {
            updated = true;
          }
        }
      }
    }
    else if(tst == TetriminoStatus.Animate)
    {
      if(millis() - as >= ad)
      {
        remove_rows();
        get_new_tetrimino();
        updated = true;
      }
    }
    return updated;
  }
   
  public void pause_the_current_game()
  {
    if(est == EngineStatus.GamePause)
    {
      est = EngineStatus.GameRun;
    }
    else if(est == EngineStatus.GameRun)
    {
      est = EngineStatus.GamePause;
    }
  }
  
  private void clean_playing_field()
  {
    for(int i = 0; i < mh; i++)
    {
      Arrays.fill(matrix[i],0);
    }
  }
  
  private void init_new_game()
  {
    // clean the playing field
    clean_playing_field();
    
    // clear the bag
    bag.clear();
    
    // set status to GameRun
    est = EngineStatus.GameRun;
    frameRate(120);
    
    // set the lock down count to 1
    ldc = 1;
    
    // set the current tetrimino status
    tst = TetriminoStatus.InPlay;
   
    // fill the tetrimino bag with 7 tetriminos
    insert_tetriminos(7);
    
    // get the first tetrimino
    get_new_tetrimino();
  }
  
  private void get_new_tetrimino()
  {
    if(rht)
    {
      ct = new Tetrimino(htt);
      rht = false;
    }
    else
    {
      // get a tetrimino from the bag
      ct = bag.remove();
      if(bag.size() == 0)
      {
          insert_tetriminos(6);
      }
      ++num_tetriminos;
    }
    
    // set the initial position of the tetrimino
    int x = 3;
    int y = 19;
    if(ct.type == TetriminoType.I)
    {
      y--;
    }
    else if(ct.type == TetriminoType.O)
    {
      x++;
    }
    ctx = x;
    cty = y;
    
    update_minos_from_current_position(true);
    
    gtd = (int)(1000 * Math.pow(0.8 - (level - 1) * 0.007, level - 1));
    
    tst = TetriminoStatus.InPlay;
    
    gts = millis();
  }
  
  private void insert_tetriminos(int num)
  {
    for(int i = 0; i < num; i++)
    {
      switch(random.nextInt(7))
      {
        case 0:
          bag.add(new Tetrimino(TetriminoType.T));
          break;
        case 1:
          bag.add(new Tetrimino(TetriminoType.L));
          break;
        case 2:
          bag.add(new Tetrimino(TetriminoType.J));
          break;
        case 3:
          bag.add(new Tetrimino(TetriminoType.I));
          break;
        case 4:
          bag.add(new Tetrimino(TetriminoType.S));
          break;
        case 5:
          bag.add(new Tetrimino(TetriminoType.Z));
          break;
        case 6:
          bag.add(new Tetrimino(TetriminoType.O));
          break;
      }
    }
  }
}
