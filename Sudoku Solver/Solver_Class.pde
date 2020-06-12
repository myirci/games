class Solver
{
  int[][] boxArray;
  int[][][] gridArray;

  /**************************************************************************************/
  /*  CONSTRUCTOR:
  /**************************************************************************************/

  Solver()
  {
    boxArray = new int[9][9];
    gridArray = new int[9][9][10];
    
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        boxArray[i][j] = -1;
        gridArray[i][j][0] = -1;
      }
    }

    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        for(int k = 1; k < 10; k++)
        {
          gridArray[i][j][k] = k;
        }
      }
    }
  }

  /**************************************************************************************/
  /*  SOLVE THE SUDOKU AND 
  /*      RETURN "0" FOR A SUCCESSFUL SOLUTION
  /*      RETURN "1" FOR AN INVALID INITIAL BOARD
  /**************************************************************************************/
  int solve()
  {
    int val = 0;
    this.syncGridArray();
    boolean valid = valid_check_board();
    if(valid == false)
    {
      return 1;
    }
    else
    {
      // Now we have a valid entry, solve the sudoku puzzle
      initial_configuration();
      do
      {
        val = checkers(); 
      }while( val!= 0);
      
      // If not solved at this step. Apply brute force.
      
      update_board();
      return 0; 
    }
  }

  int checkers()
  {
    int update = 0;
    int var1 = 0;
    boolean var2 = false;
    boolean var3 = false;
    boolean var4 = false;
    
    // First Checker: 
    do {
      restrict_possibilities();
      var1 = update_gridArray_0();
      update += var1;
    } while(var1 != 0);

    // Second Checker:
    restrict_possibilities();
    do {
      var2 = false;
      for(int i = 0; i < 9; i++)
      {
        for(int j = 0; j < 9; j++)
        {
          if(gridArray[i][j][0] == -1)
          {
            if(checker_row(i,j))
            {
              restrict_possibilities();
              var2 = true;
              update++;
            }
          }
        }
      }
    }while(var2);

    // Third Checker:
    restrict_possibilities();
    do{
      var3 = false;
      for(int i = 0; i < 9; i++)
      {
        for(int j = 0; j < 9; j++)
        {
          if(gridArray[i][j][0] == -1)
          {
            if(checker_col(i,j))
            {
              restrict_possibilities();
              var3 = true;
              update++;
            }
          }
        }
      }
    }while(var3);
       
    // Fourth Checker:
    restrict_possibilities();
    do{
      var4 = false;
      for(int i = 0; i < 9; i++)
      {
        for(int j = 0; j < 9; j++)
        {
          if(gridArray[i][j][0] == -1)
          {
            if(checker_mbox(i,j))
            {
              restrict_possibilities();
              var4 = true;
              update++;
            }
          }
        }
      }
    }while(var4);
    
    return update;
  } 
  /**************************************************************************************/
  /*  PRINT THE boxArray[i][j] ARRAY: 0 <= i,j < = 9
  /**************************************************************************************/
  void print_boxArray()
  {
    for(int i = 0; i < 9; i += 3)
    {
      println(boxArray[i][0]   + " " + boxArray[i][1]   + " " + boxArray[i][2]   + "\t" +
        boxArray[i+1][0] + " " + boxArray[i+1][1] + " " + boxArray[i+1][2] + "\t" +
        boxArray[i+2][0] + " " + boxArray[i+2][1] + " " + boxArray[i+2][2]);

      println(boxArray[i][3]   + " " + boxArray[i][4]   + " " + boxArray[i][5]   + "\t" +
        boxArray[i+1][3] + " " + boxArray[i+1][4] + " " + boxArray[i+1][5] + "\t" +
        boxArray[i+2][3] + " " + boxArray[i+2][4] + " " + boxArray[i+2][5]);

      println(boxArray[i][6]   + " " + boxArray[i][7]   + " " + boxArray[i][8]   + "\t" +
        boxArray[i+1][6] + " " + boxArray[i+1][7] + " " + boxArray[i+1][8] + "\t" +
        boxArray[i+2][6] + " " + boxArray[i+2][7] + " " + boxArray[i+2][8]);
    }
  }

  /**************************************************************************************/
  /*  PRINT THE gridArray[i][j][k] ARRAY: 0 <= i,j < 9, 0 <= k < 10 
  /**************************************************************************************/
  void print_gridArray_board(int k)
  {
    println("");
    for(int i = 0; i < 9; i++)
    {
      println(gridArray[i][0][k] + " " + gridArray[i][1][k] + " " + gridArray[i][2][k] + "\t" +
        gridArray[i][3][k] + " " + gridArray[i][4][k] + " " + gridArray[i][5][k] + "\t" +
        gridArray[i][6][k] + " " + gridArray[i][7][k] + " " + gridArray[i][8][k]);
    }
    println("");
  }

  /**************************************************************************************/
  /*  PRINT THE gridArray[i][j][k] ARRAY: i,j CONSTANT 0 <= k < 10 
  /**************************************************************************************/
  void print_gridArray_box(int i, int j)
  {
    println();
    println(gridArray[i][j][0] + "\t" + gridArray[i][j][1] + "\t" + gridArray[i][j][2] + "\t" + gridArray[i][j][3] + "\t" + gridArray[i][j][4] + "\t" + 
      gridArray[i][j][5] + "\t" + gridArray[i][j][6] + "\t" + gridArray[i][j][7] + "\t" + gridArray[i][j][8] + "\t" + gridArray[i][j][9] + "\t");
    println();
  }

  /**************************************************************************************/
  /*  COPY THE boxArray[i][j] TO gridArray[i][j][0] ARRAY: 0 <= i,j < = 9 
  /**************************************************************************************/
  void syncGridArray()
  {
    for(int i = 0; i < 9; i+=3)
    {
      gridArray[i][0][0] = boxArray[i][0];
      gridArray[i][1][0] = boxArray[i][1];
      gridArray[i][2][0] = boxArray[i][2];
      gridArray[i][3][0] = boxArray[i+1][0];
      gridArray[i][4][0] = boxArray[i+1][1];
      gridArray[i][5][0] = boxArray[i+1][2];
      gridArray[i][6][0] = boxArray[i+2][0];
      gridArray[i][7][0] = boxArray[i+2][1];
      gridArray[i][8][0] = boxArray[i+2][2];

      gridArray[i+1][0][0] = boxArray[i][3];
      gridArray[i+1][1][0] = boxArray[i][4];
      gridArray[i+1][2][0] = boxArray[i][5];
      gridArray[i+1][3][0] = boxArray[i+1][3];
      gridArray[i+1][4][0] = boxArray[i+1][4];
      gridArray[i+1][5][0] = boxArray[i+1][5];
      gridArray[i+1][6][0] = boxArray[i+2][3];
      gridArray[i+1][7][0] = boxArray[i+2][4];
      gridArray[i+1][8][0] = boxArray[i+2][5];

      gridArray[i+2][0][0] = boxArray[i][6];
      gridArray[i+2][1][0] = boxArray[i][7];
      gridArray[i+2][2][0] = boxArray[i][8];
      gridArray[i+2][3][0] = boxArray[i+1][6];
      gridArray[i+2][4][0] = boxArray[i+1][7];
      gridArray[i+2][5][0] = boxArray[i+1][8];
      gridArray[i+2][6][0] = boxArray[i+2][6];
      gridArray[i+2][7][0] = boxArray[i+2][7];
      gridArray[i+2][8][0] = boxArray[i+2][8];
    }
  }

  /**************************************************************************************/
  /*  COPY THE gridArray[i][j][0] TO boxArray[i][j] ARRAY: 0 <= i,j < = 9 
  /**************************************************************************************/
  void syncBoxArray()
  {
    for(int i = 0; i < 9; i+=3)
    {
      boxArray[i][0]   = gridArray[i][0][0];
      boxArray[i][1]   = gridArray[i][1][0];
      boxArray[i][2]   = gridArray[i][2][0];
      boxArray[i+1][0] = gridArray[i][3][0];
      boxArray[i+1][1] = gridArray[i][4][0];
      boxArray[i+1][2] = gridArray[i][5][0];
      boxArray[i+2][0] = gridArray[i][6][0];
      boxArray[i+2][1] = gridArray[i][7][0];
      boxArray[i+2][2] = gridArray[i][8][0];

      boxArray[i][3]   = gridArray[i+1][0][0];
      boxArray[i][4]   = gridArray[i+1][1][0];
      boxArray[i][5]   = gridArray[i+1][2][0];
      boxArray[i+1][3] = gridArray[i+1][3][0]; 
      boxArray[i+1][4] = gridArray[i+1][4][0];
      boxArray[i+1][5] = gridArray[i+1][5][0];
      boxArray[i+2][3] = gridArray[i+1][6][0];
      boxArray[i+2][4] = gridArray[i+1][7][0];
      boxArray[i+2][5] = gridArray[i+1][8][0];

      boxArray[i][6]   = gridArray[i+2][0][0];
      boxArray[i][7]   = gridArray[i+2][1][0];
      boxArray[i][8]   = gridArray[i+2][2][0]; 
      boxArray[i+1][6] = gridArray[i+2][3][0];
      boxArray[i+1][7] = gridArray[i+2][4][0];
      boxArray[i+1][8] = gridArray[i+2][5][0];
      boxArray[i+2][6] = gridArray[i+2][6][0];
      boxArray[i+2][7] = gridArray[i+2][7][0]; 
      boxArray[i+2][8] = gridArray[i+2][8][0];
    }
  }

  /**************************************************************************************/
  /*  CHECK THE CURRENT VALIDTY OF THE INNER BOXES. 
  /*      VALID IF NO DUBLICATE
  /*      INVALID IF DUPLICATE
  /**************************************************************************************/
  boolean valid_check_mboxes()
  {
    boolean r = true;
    int[] hit = {
      0,0,0,0,0,0,0,0,0    };

    // Check inner middle boxes:
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        if(boxArray[i][j] != -1)
        {
          hit[boxArray[i][j] - 1]++;
        }
      }

      for(int k = 0; k < 9; k++)
      {
        if(hit[k] > 1)
        {
          r = false;
          break;
        }
        hit[k] = 0;
      }

      if(r == false)
      {
        break;
      }
    }
    return r;
  }

  /**************************************************************************************/
  /*  CHECK THE CURRENT VALIDTY OF THE ROWS. 
  /*      VALID IF NO DUBLICATE
  /*      INVALID IF DUPLICATE
  /**************************************************************************************/
  boolean valid_check_rows()
  {
    boolean r = true;
    int[] hit = {
      0,0,0,0,0,0,0,0,0    };

    // Check horizontal lines
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        if(gridArray[i][j][0] != -1)
        {
          hit[gridArray[i][j][0] - 1]++;
        }
      }

      for(int k = 0; k < 9; k++)
      {
        if(hit[k] > 1)
        {
          r = false;
          break;
        }
        hit[k] = 0;
      }

      if(r == false)
      {
        break;
      }
    }
    return r;
  }

  /**************************************************************************************/
  /*  CHECK THE CURRENT VALIDTY OF THE INNER COLUMNS. 
  /*      VALID IF NO DUBLICATE
  /*      INVALID IF DUPLICATE
  /**************************************************************************************/
  boolean valid_check_columns()
  {
    boolean r = true;
    int[] hit = {
      0,0,0,0,0,0,0,0,0    };

    // Check horizontal lines
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        if(gridArray[j][i][0] != -1)
        {
          hit[gridArray[j][i][0] - 1]++;
        }
      }

      for(int k = 0; k < 9; k++)
      {
        if(hit[k] > 1)
        {
          r = false;
          break;
        }
        hit[k] = 0;
      }

      if(r == false)
      {
        break;
      }
    }
    return r;
  }

  /**************************************************************************************/
  /*  CHECK IF THE GIVEN INITIAL BOARDS IS EMPTY OR NOT 
  /*      VALID IF NOT EMPTY
  /*      INVALID IF EMPTY
  /**************************************************************************************/
  boolean check_board_not_empty() 
  {
    // This function returns true if board is not empty, otherwise returns false.
    boolean r = false;

    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        if(boxArray[i][j] != -1)
        {
          r = true;
          break;
        }
      }
      if(r == true)
      {
        break;
      }
    }   
    return r;
  }

  /**************************************************************************************/
  /*  COMBINE THE FOUR CHECKS AND DECIDE WHETHER THE CURRENT STATUS IS VALID OR NOT
  /*      VALID IF 
  /*          COLUMN CHECK IS VALID
  /*          ROW CHECK IS VALID
  /*          MBOX  CHECK IS VALID
  /*          NOT EMPTY
  /*      INVALID IF ONE OF THE FOUR CHECK IS INVALID
  /**************************************************************************************/
  boolean valid_check_board()
  {
    if(valid_check_columns() && valid_check_rows() && valid_check_mboxes() && check_board_not_empty())
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  /**************************************************************************************/
  /*  BEFORE BEGINNING TO SOLUTION, FOR THE INITIAL NUMBERS UPDATE THE POSSIBILITIES.
  /*  SINCE THESE NUMBERS ARE GIVEN INITIALLY JUST SET THE POSSIBILITIES TO "-1" TO  
  /*  INDICATE THE VALUES OF THE CORRESPPONDING BOXES ARE FOUND.
  /**************************************************************************************/
  void initial_configuration()
  {
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        if(gridArray[i][j][0] != -1)
        {
          for(int k = 1; k < 10; k++)
          {
            gridArray[i][j][k] = -1;
          }
        }
        else
        {
          for(int k = 1; k < 10; k++)
          {
            gridArray[i][j][k] = k;
          }
        }
      }
    }
  }

  /**************************************************************************************/
  /*  CHECK IF A GIVEN VALUE IS POSSIBLE FOR A LITTLE BOX
  /*      RETURN true IF val IS A POSSIBLE VALUE
  /*      RETURN false IF val IS NOT A POSSIBLE VALUE
  /**************************************************************************************/
  boolean check_value(int row, int col, int val)
  {
    boolean r = true;
    // first check the row
    for(int j = 0; j < 9; j++)
    {
      if(gridArray[row][j][0] == val)
      {
        r = false;
        break;
      }
    }
    // second check the column
    if(r)
    {
      for(int i = 0; i < 9; i++)
      {
        if(gridArray[i][col][0] == val)
        {
          r = false;
          break;
        }
      }
    }
    // third check the box
    if(r)
    {
      // box-0:
      if(row < 3 && col < 3)
      {
        for(int i = 0; i < 3; i++)
        {
          for(int j = 0; j < 3; j++)
          {
            if(gridArray[i][j][0] == val)
            {
              r = false;
              break;
            }
          }
          if(r == false)
          {
            break;
          }
        }
      }
      // box-1:
      else if(row < 3 && col < 6)
      {
        for(int i = 0; i < 3; i++)
        {
          for(int j = 3; j < 6; j++)
          {
            if(gridArray[i][j][0] == val)
            {
              r = false;
              break;
            }
          }
          if(r == false)
          {
            break;
          }
        }
      }
      // box-2:
      else if(row < 3 && col < 9)
      {
        for(int i = 0; i < 3; i++)
        {
          for(int j = 6; j < 9; j++)
          {
            if(gridArray[i][j][0] == val)
            {
              r = false;
              break;
            }
          }
          if(r == false)
          {
            break;
          }
        }
      }
      // box-3:
      else if(row < 6 && col < 3)
      {
        for(int i = 3; i < 6; i++)
        {
          for(int j = 0; j < 3; j++)
          {
            if(gridArray[i][j][0] == val)
            {
              r = false;
              break;
            }
          }
          if(r == false)
          {
            break;
          }
        }
      }
      // box-4:
      else if(row < 6 && col < 6)
      {
        for(int i = 3; i < 6; i++)
        {
          for(int j = 3; j < 6; j++)
          {
            if(gridArray[i][j][0] == val)
            {
              r = false;
              break;
            }
          }
          if(r == false)
          {
            break;
          }
        }
      }
      // box-5:
      else if(row < 6 && col < 9)
      {
        for(int i = 3; i < 6; i++)
        {
          for(int j = 6; j < 9; j++)
          {
            if(gridArray[i][j][0] == val)
            {
              r = false;
              break;
            }
          }
          if(r == false)
          {
            break;
          }
        }
      }
      // box-6:
      else if(row < 9 && col < 3)
      {
        for(int i = 6; i < 9; i++)
        {
          for(int j = 0; j < 3; j++)
          {
            if(gridArray[i][j][0] == val)
            {
              r = false;
              break;
            }
          }
          if(r == false)
          {
            break;
          }
        }
      }
      // box-7:
      else if(row < 9 && col < 6)
      {
        for(int i = 6; i < 9; i++)
        {
          for(int j = 3; j < 6; j++)
          {
            if(gridArray[i][j][0] == val)
            {
              r = false;
              break;
            }
          }
          if(r == false)
          {
            break;
          }
        }
      }
      // box-8:
      else if(row < 9 && col < 9)
      {
        for(int i = 6; i < 9; i++)
        {
          for(int j = 6; j < 9; j++)
          {
            if(gridArray[i][j][0] == val)
            {
              r = false;
              break;
            }
          }
          if(r == false)
          {
            break;
          }
        }
      }
    }

    return r;
  }

  /**************************************************************************************/
  /*  SET THE NOT POSSIBLE VALUES TO -1 IN THE gridArray[][][] ARRAY
  /**************************************************************************************/
  void restrict_possibilities()
  {
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        if(gridArray[i][j][0] == -1)
        {
          for(int k = 1; k < 10; k++)
          {
            if(gridArray[i][j][k] != -1)
            {
              if(check_value(i,j,k))
              {
                gridArray[i][j][k] = k;
              }
              else
              {
                gridArray[i][j][k] = -1;
              }
            }
          }
        }
      }
    }
  }

  /**************************************************************************************/
  /*  UPDATES THE gridArray[][][] ARRAY ACCORDING TO POSSIBILITIES AND RETURN NUMBER OF UPDATE
  /**************************************************************************************/
  int update_gridArray_0()
  {
    int count = 0;
    int[] la = new int[9];
    int i = 0;
    int j = 0;
    for(i = 0; i < 9; i++)
    {
      for(j = 0; j < 9; j++)
      {
        if(gridArray[i][j][0] == -1)
        {
          for(int k = 1; k < 10; k++)
          {
            la[k-1] = gridArray[i][j][k];
          }
          la = sort(la);
          la = reverse(la);

          if(la[1] == -1)
          {
            count++;
            gridArray[i][j][0] = la[0]; 
            for(int t = 1; t <10; t++)
            {
              gridArray[i][j][t] = -1;
            }            
          }
        }
      }
    } 
    return count;
  }
  /**************************************************************************************/
  /*  UPDATES THE BOARD 
  /**************************************************************************************/
  void update_board()
  {
    int[][] pboxArray = new int[9][9];
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        pboxArray[i][j] = boxArray[i][j];
      }
    }

    syncBoxArray();

    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        if(boxArray[i][j] != pboxArray[i][j])
        {
          myBoard.boxes[i].boxes[j].textColor = color2;
        }
        myBoard.boxes[i].boxes[j].num = boxArray[i][j];
      }
    }
  }

  /**************************************************************************************/
  /*  UPDATES THE LITTLE BOX BY LOOKING AT THE POSSIBLE VALUES OF THE OTHER EMPTY BOXES AT THE SAME ROW
  /*        RETURN true IF THE CONTENT OF THE LITTLE BOX IS UPDATED
  /*        RETURN false IF THE CONTENT OF THE LITTLE BOX IS NOT UPDATED
  /**************************************************************************************/
  boolean checker_row(int row, int col)
  {
    boolean r = false;
    for(int k = 1; k < 10; k++)
    {
      if(gridArray[row][col][k] != -1)
      {
        if(search_row_possible_values(row, col, gridArray[row][col][k]))
        {
           
          gridArray[row][col][0] = gridArray[row][col][k];
          for(int t = 1; t < 10; t++)
          {
            gridArray[row][col][t] = -1;
          }
          break;  
        }
      }
    }  
    return r;  
  }

  /**************************************************************************************/
  /*  UPDATES THE LITTLE BOX BY LOOKING AT THE POSSIBLE VALUES OF THE OTHER EMPTY BOXES AT THE SAME COLUMN
  /*        RETURN true IF THE CONTENT OF THE LITTLE BOX IS UPDATED
  /*        RETURN false IF THE CONTENT OF THE LITTLE BOX IS NOT UPDATED
  /**************************************************************************************/
  boolean checker_col(int row, int col)
  {
    boolean r = false;
    for(int k = 1; k < 10; k++)
    {
      if(gridArray[row][col][k] != -1)
      {
        if(search_col_possible_values(row,col,gridArray[row][col][k]))
        {
          r = true;
          gridArray[row][col][0] = gridArray[row][col][k];
          for(int t = 1; t < 10; t++)
          {
            gridArray[row][col][t] = -1;
          }
          break; 
        }
      }
    }
    return r;
  }

  /**************************************************************************************/
  /*  UPDATES THE LITTLE BOX BY LOOKING AT THE POSSIBLE VALUES OF THE OTHER EMPTY BOXES AT THE SAME MBOX
  /*        RETURN true IF THE CONTENT OF THE LITTLE BOX IS UPDATED
  /*        RETURN false IF THE CONTENT OF THE LITTLE BOX IS NOT UPDATED
  /**************************************************************************************/
  boolean checker_mbox(int row, int col)
  {
    boolean r = false;

    for(int k = 1; k < 10; k++)
    {
      if(gridArray[row][col][k] != -1)
      {
        if(search_mbox_possible_values(row,col,gridArray[row][col][k]))
        {
          r = true;
          gridArray[row][col][0] = gridArray[row][col][k];
          for(int t = 1; t < 10; t++)
          {
            gridArray[row][col][t] = -1;
          }
          break; 
        }
      }
    }
    return r;    
  }

  /**************************************************************************************/
  /*  SEARCH THE OTHER BOXES IN A ROW FOR THEIR POSSIBLE VALUES FOR A GIVEN VALUE
  /*      RETURN true IF THE val DOES NOT EXIST IN THE POSSIBLE VALUES OF THE OTHER BOXES
  /*      RETURN false IF THE val EXISTS IN THE POSSIBLE VALUES OF THE OTHER BOXES
  /**************************************************************************************/
  boolean search_row_possible_values(int row, int col, int val)
  {
    // val is not equal to -1
    boolean r = true;
    for(int j = 0; j < 9; j++)
    {
      if(j != col && gridArray[row][j][0] == -1)
      {
        for(int k = 1; k < 10; k++)
        {
          if(val == gridArray[row][j][k])
          {
            r = false;
            break;
          }
        }
        if(!r)
        {
          break;
        }
      }
    }
    return r;
  }

  /**************************************************************************************/
  /*  SEARCH THE OTHER BOXES IN A COLUMN FOR THEIR POSSIBLE VALUES FOR A GIVEN VALUE
  /*      RETURN true IF THE val DOES NOT EXIST IN THE POSSIBLE VALUES OF THE OTHER BOXES
  /*      RETURN false IF THE val EXISTS IN THE POSSIBLE VALUES OF THE OTHER BOXES
  /**************************************************************************************/
  boolean search_col_possible_values(int row, int col, int val)
  {
    // val is not equal to -1
    boolean r = true;
    for(int i = 0; i < 9; i++)
    {
      if(i != row && gridArray[i][col][0] == -1)
      {
        for(int k = 1; k < 10; k++)
        {
          if(val == gridArray[i][col][k])
          {
            r = false;
            break;
          }
        }
        if(!r)
        {
          break;
        }
      }
    }
    return r;
  }
  /**************************************************************************************/
  /*  SEARCH THE OTHER BOXES IN A MBOX FOR THEIR POSSIBLE VALUES FOR A GIVEN VALUE
  /*      RETURN true IF THE val DOES NOT EXIST IN THE POSSIBLE VALUES OF THE OTHER BOXES
  /*      RETURN false IF THE val EXISTS IN THE POSSIBLE VALUES OF THE OTHER BOXES
  /**************************************************************************************/
  boolean search_mbox_possible_values(int row, int col, int val)
  {
    // val is not equal to -1
    boolean r = true;
    // box-0:
    if(row < 3 && col < 3)
    {
      for(int i = 0; i < 3; i++)
      {
        for(int j = 0; j < 3; j++)
        {
          if((i != row || j != col) && gridArray[i][j][0] == -1)
          {
            for(int k = 1; k < 10; k++)
            {
              if(val == gridArray[i][j][k])
              {
                r = false;
                break;
              }
            }
            if(!r)
            {
              break;
            }
          }
        }
        if(!r)
        {
          break;
        }
      }
    }
    // box-1:
    else if(row < 3 && col < 6)
    {
      for(int i = 0; i < 3; i++)
      {
        for(int j = 3; j < 6; j++)
        {
          if((i != row || j != col) && gridArray[i][j][0] == -1)
          {
            for(int k = 1; k < 10; k++)
            {
              if(val == gridArray[i][j][k])
              {
                r = false;
                break;
              }
            }
            if(!r)
            {
              break;
            }
          }
        }
        if(!r)
        {
          break;
        }
      }
    }
    // box-2:
    else if(row < 3 && col < 9)
    {
      for(int i = 0; i < 3; i++)
      {
        for(int j = 6; j < 9; j++)
        {
          if((i != row || j != col) && gridArray[i][j][0] == -1)
          {
            for(int k = 1; k < 10; k++)
            {
              if(val == gridArray[i][j][k])
              {
                r = false;
                break;
              }
            }
            if(!r)
            {
              break;
            }
          }
        }
        if(!r)
        {
          break;
        }
      }
    }
    // box-3:
    else if(row < 6 && col < 3)
    {
      for(int i = 3; i < 6; i++)
      {
        for(int j = 0; j < 3; j++)
        {
          if((i != row || j != col) && gridArray[i][j][0] == -1)
          {
            for(int k = 1; k < 10; k++)
            {
              if(val == gridArray[i][j][k])
              {
                r = false;
                break;
              }
            }
            if(!r)
            {
              break;
            }
          }
        }
        if(!r)
        {
          break;
        }
      }
    }
    // box-4:
    else if(row < 6 && col < 6)
    {
      for(int i = 3; i < 6; i++)
      {
        for(int j = 3; j < 6; j++)
        {
          if((i != row || j != col) && gridArray[i][j][0] == -1)
          {
            for(int k = 1; k < 10; k++)
            {
              if(val == gridArray[i][j][k])
              {
                r = false;
                break;
              }
            }
            if(!r)
            {
              break;
            }
          }
        }
        if(!r)
        {
          break;
        }
      }
    }
    // box-5:
    else if(row < 6 && col < 9)
    {
      for(int i = 3; i < 6; i++)
      {
        for(int j = 6; j < 9; j++)
        {
          if((i != row || j != col) && gridArray[i][j][0] == -1)
          {
            for(int k = 1; k < 10; k++)
            {
              if(val == gridArray[i][j][k])
              {
                r = false;
                break;
              }
            }
            if(!r)
            {
              break;
            }
          }
        }
        if(!r)
        {
          break;
        }
      }
    }
    // box-6:
    else if(row < 9 && col < 3)
    {
      for(int i = 6; i < 9; i++)
      {
        for(int j = 0; j < 3; j++)
        {
          if((i != row || j != col) && gridArray[i][j][0] == -1)
          {
            for(int k = 1; k < 10; k++)
            {
              if(val == gridArray[i][j][k])
              {
                r = false;
                break;
              }
            }
            if(!r)
            {
              break;
            }
          }
        }
        if(!r)
        {
          break;
        }
      }
    }
    // box-7:
    else if(row < 9 && col < 6)
    {
      for(int i = 6; i < 9; i++)
      {
        for(int j = 3; j < 6; j++)
        {
          if((i != row || j != col) && gridArray[i][j][0] == -1)
          {
            for(int k = 1; k < 10; k++)
            {
              if(val == gridArray[i][j][k])
              {
                r = false;
                break;
              }
            }
            if(!r)
            {
              break;
            }
          }
        }
        if(!r)
        {
          break;
        }
      }
    }
    // box-8:
    else if(row < 9 && col < 9)
    {
      for(int i = 6; i < 9; i++)
      {
        for(int j = 6; j < 9; j++)
        {
          if((i != row || j != col) && gridArray[i][j][0] == -1)
          {
            for(int k = 1; k < 10; k++)
            {
              if(val == gridArray[i][j][k])
              {
                r = false;
                break;
              }
            }
            if(!r)
            {
              break;
            }
          }
        }
        if(!r)
        {
          break;
        }
      }
    } 
    return r;
  }
  /**************************************************************************************/
  /*  CHECK IF THE SUDOKU PUZZLE IS SOLVED
  /*        RETURN true  IF SOLVED
  /*        RETURN false IF SOLVED
  /**************************************************************************************/
  boolean solved()
  {
    boolean r = true;

    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        if( gridArray[i][j][0] == -1)
        {
          r = false;
          break;  
        }
      }
      if(!r)
      {
        break;
      }
    }

    if(r)
    {
      if(!valid_check_board())
      {
        r = false;
      }
    }
    return r;
  }


}




