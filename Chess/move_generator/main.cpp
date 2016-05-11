#include <iostream>

enum color : std::uint8_t {
    White,
    Black
};

enum square : std::uint8_t {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8
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

square print_order[64] = {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

enum piece : std::int8_t {
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

char piece_to_char(piece p) {
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

enum move_type : std::uint8_t {
    quite = 0,
    double_pawn_push,   // 1
    king_side_castle,   // 2
    queen_side_castle,  // 3
    capture,            // 4s
    en_passant_capture, // 5
    knight_promotion = 8,
    bishop_promotion,   // 9
    rook_promotion,     // 10
    ...
};

struct move {

    mv(std::uint8_t from, std::uint8_t to, piece captured = Empty) { }
    std::uint16_t mv;

};

struct board {

    board() {
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

    void print_board() const {

        for(int i = 0; i < 64; ++i) {
            if(i > 0 && i % 8 == 0)
                std::cout << std::endl;
            std::cout << piece_to_char(brd[print_order[i]]) << " ";
        }
        std::cout << std::endl;
    }

    piece brd[64];
};

int main(void) {

    board b;
    b.print_board();

}
