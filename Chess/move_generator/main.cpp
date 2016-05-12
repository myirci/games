#include <iostream>
#include <sstream>
#include <vector>
#include <array>

enum Color : std::uint8_t {
    Black,
    White
};

enum Castling : std::uint8_t {
    King_side,
    Queen_side
};

enum Square : std::uint8_t {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8,
    Outside
};

inline std::uint8_t rank(std::uint8_t s) { return s / 8; }
inline std::uint8_t file(std::uint8_t s) { return s % 8; }
inline Square sq(std::uint8_t rank_no, std::uint8_t file_no) { return static_cast<Square>(8*rank_no + file_no); }

std::string square_to_string[64] = {
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"
};

Square print_order[64] = {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

enum Piece : std::int8_t {
    Empty   = 0,
    WPawn   = 1,
    WRook   = 2,
    WKnight = 3,
    WBishop = 4,
    WQueen  = 5,
    WKing   = 6,
    BPawn   = -WPawn,
    BRook   = -WRook,
    BKnight = -WKnight,
    BBishop = -WBishop,
    BQueen  = -WQueen,
    BKing   = -WKing
};

inline Piece char_to_piece(char c) {

    switch(c) {
    case 'P':
        return WPawn;
        break;
    case 'p':
        return BPawn;
        break;
    case 'K':
        return WKing;
        break;
    case 'k':
        return BKing;
        break;
    case 'R':
        return WRook;
        break;
    case 'r':
        return BRook;
        break;
    case 'N':
        return WKnight;
        break;
    case 'n':
        return BKnight;
        break;
    case 'B':
        return WBishop;
        break;
    case 'b':
        return BBishop;
        break;
    case 'Q':
        return WQueen;
        break;
    case 'q':
        return BQueen;
        break;
    default:
        return Empty;
        break;
    }
}

inline char piece_to_char(Piece p) {
    switch(p) {
    case Empty:
        return '.';
        break;
    case WPawn:
        return 'P';
        break;
    case BPawn:
        return 'p';
        break;
    case WKing:
        return 'K';
        break;
    case BKing:
        return 'k';
        break;
    case WRook:
        return 'R';
        break;
    case BRook:
        return 'r';
        break;
    case WKnight:
        return 'N';
        break;
    case BKnight:
        return 'n';
        break;
    case WBishop:
        return 'B';
        break;
    case BBishop:
        return 'b';
        break;
    case WQueen:
        return 'Q';
        break;
    case BQueen:
        return 'q';
        break;
    default:
        return 'X';
        break;
    }
}

enum Move_flag : std::uint8_t {
    Quite = 0,
    Double_Pawn_Push,           // 1
    King_Side_Castle,           // 2
    Queen_Side_Castle,          // 3
    Capture,                    // 4
    En_Passant_Capture,         // 5
    Knight_Promotion = 8,
    Bishop_Promotion,           // 9
    Rook_Promotion,             // 10
    Queen_Promotion,            // 11
    Knight_Promotion_Capture,   // 12
    Bishop_Promotion_Capture,   // 13
    Rook_Promotion_Capture,     // 14
    Queen_Promotion_Capture     // 15
};

class Move {
public:

    Move(std::uint8_t from, std::uint8_t to, Move_flag mflag) { }

    Move(const Move& m) { mv = m.mv; }

    std::uint8_t get_from() const {
        return static_cast<std::uint8_t>((mv & 0xFC00) >> 10);
    }

    std::uint8_t get_to() const {
        return static_cast<std::uint8_t>((mv & 0x03F0) >> 4);
    }

    Move_flag get_flag() const {
        return static_cast<Move_flag>(mv & 0x000F);
    }

private:

    void set_from(std::uint8_t from) {
        mv &= 0x03FF;
        mv |= (static_cast<std::uint16_t>(from) << 10);
    }

    void set_to(std::uint8_t to) {
        mv &= 0xFC0F;
        mv |= (static_cast<std::uint16_t>(to) << 4);
    }

    void set_move_flag(std::uint8_t mflag) {
        mv &= 0xFFF0;
        mv |= static_cast<std::uint16_t>(mflag);
    }

    std::uint16_t mv;
};

class Extended_move : public Move {
public:
    Extended_move(Move m, Piece captured_piece) : Move(m), captured(captured_piece) { }
    Piece captured;
    // 8-bit additional space is also avaliable!
};

struct Board {

    Board() {
        brd[a1] = brd[h1] = WRook;
        brd[b1] = brd[g1] = WKnight;
        brd[c1] = brd[f1] = WBishop;
        brd[d1] = WQueen;
        brd[e1] = WKing;
        for(std::uint8_t s = a2; s <= h2; ++s) brd[s] = WPawn;
        for(std::uint8_t s = a3; s <= h6; ++s) brd[s] = Empty;
        for(std::uint8_t s = a7; s <= h7; ++s) brd[s] = BPawn;
        brd[a8] = brd[h8] = BRook;
        brd[b8] = brd[g8] = BKnight;
        brd[c8] = brd[f8] = BBishop;
        brd[d8] = BQueen;
        brd[e8] = BKing;
    }

    void make_move(const Move& m) {

    }

    void make_move(const Extended_move& m) {

    }

    void undo_move(const Move& m) {

    }

    void undo_move(const Extended_move& m) {

    }

    void set_side_to_move(Color c) { (c == White) ? (flags |= 1) : (flags &= 0xFE); }

    Color get_side_to_move() const { return static_cast<Color>(flags & 1); }

    void set_castling_rights(Color clr, Castling cst) {
        (clr == White)     ? (flags |= 2) : (flags &= 0xFD);
        (cst == King_side) ? (flags |= 4) : (flags &= 0xFB);
    }

    bool check_castling_availability(Color clr, Castling cst) const {

    }

    void set_captured_piece(Piece p) {

    }

    Piece get_captured_piece() const {

    }

    void print_board() const {

        for(int i = 0; i < 64; ++i) {
            if(i > 0 && i % 8 == 0)
                std::cout << std::endl;
            std::cout << piece_to_char(brd[print_order[i]]) << " ";
        }
        std::cout << std::endl;
    }

    Piece brd[64];
    Square en_passant_sq;
    std::uint8_t flags; // [Free to use -> 1 bit][Captured piece-> 4 bits] [Castling-> 2 bits] [Color-> 1 bit]
    std::uint8_t fifty_move_counter;
    std::uint16_t move_counter;
};

class move_generator {
public:

    void generate_knight_moves_extended(const Board& b, std::vector<Extended_move>& moves) {



    }

private:

};


/*
FEN: Forsyth-Edwards Notation
Field-1: Piece Placement
Field-2: Active Color
Field-3: Castling Availability
Field-4: En Passant
Field-5: Half Move Clock
Field-6: Full Move Number

Here are some example positions in FEN notation:
Pos-1: 6k1/pp3pp1/3p4/2pP2p1/4Pp2/8/1P3PP1/6K1 b KQkq c6 1 2
Pos-2: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
Pos-3: r1bq1rk1/4bppp/p3pn2/1pn3B1/8/P1NBPN2/1P3PPP/R2Q1RK1
*/

class FEN {
public:
    FEN() : fen_str{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"} { }

    FEN(const std::string& fen) : fen_str{fen} { }

    void set_fen(const std::string& fen) { fen_str = fen; }

    void set_fen(std::string&& fen)      { fen_str = std::move(fen); }

    const std::string& get_fen() const   {return fen_str; }

    void to_board(Board& b) const {

        std::array<std::string, 6> fields;
        parse(fields);

        // Field-1: Piece placement
        std::istringstream is{fields[0]};
        std::string str{""};
        for(int i = 0; i < 8; ++i) {
            std::getline(is, str, '/');
            int f{-1};
            for(int j = 0; j < str.length(); ++j) {
                if(std::isdigit(str[j]))
                    for(int k = 0; k < int(str[j] - '0'); ++k)
                        b.brd[sq(7-i, ++f)] = Empty;
                else b.brd[sq(7-i, ++f)] = char_to_piece(str[j]);
            }
        }

        // Field-2: Active color
        if(fields[1] == "w") b.set_side_to_move(White);
        else b.set_side_to_move(Black);

        // Field-3: Castling Availability

        // Field-4: En Passant
        (fields[3] == "-") ? b.en_passant_sq = Outside : b.en_passant_sq = sq(fields[3][1] - '1', fields[3][0] - 'a');

        // Field-5: Half Move Clock
        b.fifty_move_counter = static_cast<std::uint8_t>(std::stoi(fields[4]));

        // Field-6: Full Move Number
        b.move_counter = static_cast<std::uint16_t>(std::stoi(fields[5]));
    }

    void parse(std::array<std::string, 6>& fields) const {
        std::istringstream ss {fen_str};
        for(int i = 0; i < 6; ++i)
            ss >> fields[i];
    }

private:
    std::string fen_str;
};

int main(void) {

    /*
    Board b;
    std::cout << sizeof(Board) << std::endl;
    b.print_board();

    FEN f("6k1/pp3pp1/3p4/2pP2p1/4Pp2/8/1P3PP1/6K1 b KQkq c6 1 2");
    f.to_board(b);
    b.print_board();
    */

    for(int i = 0; i < 4; ++i) {
        std::cout << (1 << i) << std::endl;
    }



}
