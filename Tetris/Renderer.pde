
public class Renderer
{
  private class GuiSchema
  {
    private final float cell_size;    
    private final float spacing;
    
    private final float playing_field_height;      
    private final float playing_field_width;
    private final float playing_field_x;
    private final float playing_field_y;
    private float[][][] coord;
    
    private final float left_panel_height;      
    private final float left_panel_width;
    private final float left_panel_x;
    private final float left_panel_y;
    
    private final float right_panel_height;      
    private final float right_panel_width;
    private final float right_panel_x;
    private final float right_panel_y;
    
    private final float drawable_x;
    private final float drawable_y;    
    private final float drawable_width;
    private final float drawable_height;

    private color ttc; // T tetrimino color
    private color ltc; // L tetrimino color
    private color jtc; // J tetrimino color
    private color itc; // I tetrimino color
    private color stc; // S tetrimino color
    private color ztc; // Z tetrimino color
    private color otc; // O tetrimino color
    private color asc; // Animation stroke color
    private color afc; // Animation fill color
    
    public GuiSchema(float cs, float sp)
    {
      cell_size = cs;
      spacing = sp;
      
      playing_field_height = 20.33 * cell_size;
      playing_field_width = 10 * cell_size;
      left_panel_width = 0.6 * playing_field_width;
      left_panel_height = playing_field_height;
      right_panel_width = left_panel_width;
      right_panel_height = playing_field_height;
      
      drawable_x = spacing;
      drawable_y = spacing;
      left_panel_x = drawable_x;
      left_panel_y = drawable_y;
      playing_field_x = drawable_x + left_panel_width + spacing;
      playing_field_y = drawable_y; 
      right_panel_x = playing_field_x + playing_field_width + spacing;
      right_panel_y = drawable_y;
      
      drawable_width = left_panel_width + spacing + playing_field_width + spacing + right_panel_width; 
      drawable_height = playing_field_height;
      
      // System.out.println(drawable_width + 2*spacing);
      // System.out.println(drawable_height + 2*spacing);
      
      coord = new float[21][10][2];
      
      float x = playing_field_x;
      float y = playing_field_y + playing_field_height - cell_size;
      for(int i = 0; i < 20; i++)
      {
        for(int j = 0; j < 10; j++)
        {
          coord[i][j][0] = x;
          coord[i][j][1] = y;
          x += cell_size;
        }
        y -= cell_size;
        x = playing_field_x;
      }
      
      y += 0.67 * cell_size;
      for(int j = 0; j < 10; j++)
      {
        coord[20][j][0] = x;
        coord[20][j][1] = y;
        x += cell_size;
      }

      ttc = color(146,39,144); // Purple
      ltc = color(248,158,40); // Orange
      jtc = color(0,120,193);  // Dark blue
      itc = color(0,173,238);  // Light blue
      stc = color(122,193,66); // Green
      ztc = color(239,46,36);  // Red
      otc = color(255,210,3);  // Yellow
      afc = color(0,0,0);   
      asc = color (255,255,204);
    }
    
    public void render_matrix(int[][] matrix)
    {
      stroke(0);
      strokeWeight(2);
      for(int i = 0; i < 21; i++)
      {
        for(int j = 0; j < 10; j++)
        {
          if(matrix[i][j] != 0)
          { 
            switch(matrix[i][j])
            {
              case 1:
                fill(ttc);
                break;
              case 2:
                fill(ltc);
                break;
              case 3:
                fill(jtc);
                break;
              case 4:
                fill(itc);
                break;
              case 5:
                fill(stc);
                break;
              case 6:
                fill(ztc);
                break;
              case 7:
                fill(otc);
                break;
              case 8:
                stroke(asc);
                strokeWeight(4);
                fill(afc);
                break;
            }
            square(coord[i][j][0], coord[i][j][1], cell_size);
            strokeWeight(2);
          }
        }
      }  
    }
    
    public void render_current_tetrimino(int[][] minos, TetriminoType t)
    {
      for(int i = 0; i < 4; i++)
      {
        if(minos[i][1] < 21)
        {
          switch(t)
          {
            case T:
              fill(ttc);
              break;
            case L:
              fill(ltc);
              break;
            case J:
              fill(jtc);
              break;
            case I:
              fill(itc);
              break;
            case S:
              fill(stc);
              break;
            case Z:
              fill(ztc);
              break;
            case O:
              fill(otc);
              break;
            }
            square(coord[minos[i][1]][minos[i][0]][0], coord[minos[i][1]][minos[i][0]][1], cell_size);
        }
      }
    }
    
    private void render_next_tetrimino(TetriminoType t, float xs, float ys, float ms)
    {
      switch(t)
      {
        case T:
        {
          fill(ttc);
          square(xs+ms, ys, ms);
          square(xs, ys+ms, ms);
          square(xs+ms, ys+ms, ms);
          square(xs+2*ms, ys+ms, ms);
          break;
        }
        case L:
        {
          fill(ltc);
          square(xs+2*ms, ys, ms);
          square(xs, ys+ms, ms);
          square(xs+ ms, ys+ms, ms);
          square(xs+2*ms, ys+ms, ms);
          break;
        }
        case J:
        {
          fill(jtc);
          square(xs, ys, ms);
          square(xs, ys+ms, ms);
          square(xs+ms, ys+ms, ms);
          square(xs+2*ms, ys+ms, ms);
          break;
        }
        case I:
        {
          fill(itc);
          square(xs, ys, ms);
          square(xs + ms, ys, ms);
          square(xs + 2*ms, ys, ms);
          square(xs + 3*ms, ys, ms);
          break;
        }
        case S:
        {
          fill(stc);
          square(xs+ms, ys, ms);
          square(xs+2*ms, ys, ms);
          square(xs,ys+ms, ms);
          square(xs+ms, ys+ms, ms);
          break; 
        }
        case Z:
        {
          fill(ztc);
          square(xs, ys, ms);
          square(xs+ms, ys, ms);
          square(xs+ms, ys+ms, ms);
          square(xs+2*ms, ys+ms, ms);
          break;
        }
        case O:
        {
          fill(otc);
          square(xs, ys, ms);
          square(xs+ms, ys, ms);
          square(xs, ys+ms, ms);
          square(xs+ms, ys+ms, ms);
          break;
        }
      }
    }
    
    public void render_next_tetriminos(Queue<Tetrimino> bag)
    {
      // ellipse: next tetrimino container
      noFill();
      stroke(75);
      strokeWeight(3);
      
      float ms = cell_size;
      
      float ellipse_width = 4*ms + 2*spacing;
      float ellipse_height = 4*ms;
      float ellipse_x = right_panel_x + right_panel_width/2.0;
      float ellipse_y = right_panel_y + spacing + ellipse_height/2.0;
      ellipse(ellipse_x, ellipse_y, ellipse_width, ellipse_height);
      
      // next tetrimino
      Tetrimino next = bag.element();
      float xsp = (ellipse_width - next.w * ms) / 2.0;
      float xs = ellipse_x - ellipse_width/2.0 + xsp;
      float ys = ellipse_y - (next.h/2.0) * ms;
      
      render_next_tetrimino(next.type, xs, ys, ms);
      
      ms = 0.9 * cell_size;
      ys = ellipse_y + ellipse_height/2.0 + 3*spacing;
      
      int i = 0;
      int th = 0;
      for(Tetrimino t : bag)
      {
        i++;
        if(i == 1)
        {
          continue;
        }
        th += t.h;
        xsp = (right_panel_width - t.w*ms) / 2.0;
        xs = right_panel_x + xsp;
        render_next_tetrimino(t.type, xs, ys, ms); 
        ys += (t.h*ms + 1.5*spacing);
      }
      
      if(i != 1)
      {
        noFill();
        rect(ellipse_x - ellipse_width/2.0, ellipse_y + ellipse_height/2.0 + 1.5 * spacing, ellipse_width, th*ms + i*1.5*spacing);
      }
    }
    
    public void render_empty_panels()
    {
      stroke(0);
      fill(255);
      rect(left_panel_x, left_panel_y, left_panel_width, left_panel_height);              // left panel
      rect(playing_field_x, playing_field_y, playing_field_width, playing_field_height);  // playing field
      rect(right_panel_x, right_panel_y, right_panel_width, right_panel_height);          // right panel
      
      stroke(grid_color);
      strokeWeight(2);
      render_grid();
    }
    
    public void render_playing_field()
    {
      render_current_tetrimino(eng.minos, eng.ct.type);
      render_matrix(eng.matrix);  
    }
       
    public void render_left_panel()
    {
      // render hold tetrimino 
      noFill();
      stroke(75);
      strokeWeight(3);
      
      float ms = cell_size;
      float ellipse_width = 4*ms + 2*spacing;
      float ellipse_height = 4*ms;
      float ellipse_x = left_panel_x + left_panel_width/2.0;
      float ellipse_y = left_panel_y + spacing + ellipse_height/2.0;
      ellipse(ellipse_x, ellipse_y, ellipse_width, ellipse_height);
      
      if(eng.ht != null)
      {
        float xsp = (ellipse_width - eng.ht.w * ms) / 2.0;
        float xs = ellipse_x - ellipse_width/2.0 + xsp;
        float ys = ellipse_y - (eng.ht.h/2.0) * ms;
        render_next_tetrimino(eng.ht.type, xs, ys, ms);
      }
      
      float x = left_panel_x + spacing;
      float y = ellipse_y + ellipse_height/2.0 + 3*spacing;
      
      // render stats
      fill(0);
      textSize(25);
      text("Score", x, y);
      text(eng.score, x, y + 2*spacing);
      
      y += 5*spacing;
      text("Level", x, y);
      text(eng.level, x, y + 2*spacing);
      
      y += 5*spacing;
      text("Lines", x, y);
      text(eng.line_clears, x, y + 2*spacing);
      
      y += 5*spacing;
      text("Goal", x, y);
      text(eng.goal, x, y + 2*spacing);
      
      y += 5*spacing;
      text("Tetris", x, y);
      text(eng.num_tetrises, x, y + 2*spacing);
      
      y += 5*spacing;
      text("Tetriminos", x, y);
      text(eng.num_tetriminos, x, y + 2*spacing);
    }
    
    public void render_right_panel()
    {  
      render_next_tetriminos(eng.bag);  
    }
    
    public void render_grid()
    {
      float x1 = playing_field_x;
      float x2 = playing_field_x + playing_field_width;
      float y = playing_field_height + spacing - cell_size;
    
      for(int i = 0; i < 20; i++)
      {
        line(x1, y, x2, y);
        y -= cell_size;
      }
    
      float y1 = playing_field_height + spacing;
      float y2 = y1 - 20 * cell_size;
      float x = playing_field_x + cell_size;
    
      for(int i = 1; i < 10; i++)
      {
        line(x, y1, x, y2);
        x += cell_size;
      }
    }
  }
  
  private GuiSchema gui;
  private Engine eng;
  private final color grid_color;
  
  public Renderer(Engine e)
  {
    eng = e;
    gui = new GuiSchema(30, 15);
    grid_color = color(0,10);
    gui.render_empty_panels();
  } 

  void display() 
  {
    gui.render_empty_panels();
    gui.render_playing_field();
    gui.render_left_panel();
    gui.render_right_panel();
  }
} 
