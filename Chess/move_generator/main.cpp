#include <iostream>
#include <vector>

enum Color : std::uint8_t {
    White,
    Black
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

inline std::uint8_t rank(std::uint8_t s)                    { return s / 8; }
std::uint8_t file(std::uint8_t s)                           { return s % 8; }
std::uint8_t sq(std::uint8_t rank_no, std::uint8_t file_no) { return static_cast<std::uint8_t>(8*rank_no + file_no); }

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

char piece_to_char(Piece p) {
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

    Board() : en_passant_sq(Outside), captured(Empty) {
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
    Piece captured;         // not needed for extended moves
};


class move_generator {
public:

    void generate_knight_moves_extended(const Board& b, std::vector<Extended_move>& moves) {



    }

private:

};

int main(void) {

    Board b;
    b.print_board();
}
