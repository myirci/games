#include <iostream>
#include <sstream>
#include <vector>
#include <array>

enum Color : std::uint8_t {
    Black,
    White
};

enum Castling : std::uint8_t {
    White_king_side = 1,
    White_queen_side = 2,
    Black_king_side = 4,
    Black_queen_side = 8
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
    Invalid_square
};

inline std::uint8_t rank(std::uint8_t s) { return s / 8; }
inline std::uint8_t file(std::uint8_t s) { return s % 8; }
inline Square sq(std::uint8_t rank_no, std::uint8_t file_no) { return static_cast<Square>(8*rank_no + file_no); }

std::string square_to_string[65] = {
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "-"
};

Square square_visit_order[64] = {
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
    Quite = 0,                  // 0        0000
    Double_Pawn_Push,           // 1        0001
    King_Side_Castle,           // 2        0010
    Queen_Side_Castle,          // 3        0011
    Capture,                    // 4        0100
    En_Passant_Capture,         // 5        0101
    Knight_Promotion = 8,       //          1000
    Bishop_Promotion,           // 9        1001
    Rook_Promotion,             // 10       1010
    Queen_Promotion,            // 11       1011
    Knight_Promotion_Capture,   // 12       1100
    Bishop_Promotion_Capture,   // 13       1101
    Rook_Promotion_Capture,     // 14       1110
    Queen_Promotion_Capture     // 15       1111
};

std::string move_flag_to_string[] = {
    "Quite", "Double_Pawn_Push", "King_Side_Castle", "Queen_Side_Castle", "Capture", "En_Passant_Capture", "-", "-",
    "Knight_Promotion", "Bishop_Promotion", "Rook_Promotion", "Queen_Promotion", "Knight_Promotion_Capture",
    "Bishop_Promotion_Capture", "Rook_Promotion_Capture", "Queen_Promotion_Capture"
};

class Move {
public:

    Move(std::uint8_t from, std::uint8_t to, Move_flag mflag) {
        set_from(from);
        set_to(to);
        set_move_flag(mflag);
    }

    Move(const Move& m) { mv = m.mv; }

    std::uint8_t get_from() const { return static_cast<std::uint8_t>((mv & 0xFC00) >> 10); }

    std::uint8_t get_to() const { return static_cast<std::uint8_t>((mv & 0x03F0) >> 4);  }

    Move_flag get_flag() const { return static_cast<Move_flag>(mv & 0x000F); }

    bool is_promotion() const { return mv & 0x0008; }

    bool is_capture() const { return mv & 0x0004; }

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

class Board {
public:

    Piece brd[64];
    std::uint8_t current_half_move_counter;
    std::uint8_t previous_half_move_counter;
    std::uint16_t move_counter;
    Piece captured;
    Square en_passant_square;
    std::uint8_t castling_rights;
    Color side_to_move;

    Board() : side_to_move{White}, castling_rights{0xFF}, captured{Empty}, en_passant_square{Invalid_square},
        current_half_move_counter{0}, previous_half_move_counter{0}, move_counter{0} {

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

    bool query_castling_rights(Castling cst) const    { return castling_rights & cst; }
    void set_castling_rights(Castling cst, bool flag) { flag ? (castling_rights |= cst) : (castling_rights &= (~cst)); }

    void make_move(const Move& m) {

        Move_flag mf {m.get_flag()};
        std::uint8_t from {m.get_from()}, to{m.get_to()};

        // update half move counter
        previous_half_move_counter = current_half_move_counter++;

        // update en passant square
        if(mf == Double_Pawn_Push) side_to_move == White ? en_passant_square = static_cast<Square>(from + 8) : en_passant_square = static_cast<Square>(from - 8);
        else en_passant_square = Invalid_square;

        // capture
        if(m.is_capture()) {
            if(mf == En_Passant_Capture) {
                if(side_to_move == White) {
                    brd[en_passant_square - 8] = Empty;
                    captured = BPawn;
                }
                else {
                    brd[en_passant_square + 8] = Empty;
                    captured = WPawn;
                }
            }
            else {
                captured = brd[to];
            }
            current_half_move_counter = 0;
        }

        switch (brd[from]) {
        case WPawn:
        case BPawn:
            current_half_move_counter = 0;
            break;
        case WRook:
            if(from == a1 && can_white_castle_queen_side()) {
                copy_castling_rights();
                set_castling_rights(White_queen_side, false);
            }
            else if(from == h1 && can_white_castle_king_side()) {
                copy_castling_rights();
                set_castling_rights(White_king_side, false);
            }
            break;
        case BRook:
            if(from == a8 && can_black_castle_queen_side()) {
                copy_castling_rights();
                set_castling_rights(Black_queen_side, false);
            }
            else if(from == h8 && can_black_castle_king_side()) {
                copy_castling_rights();
                set_castling_rights(Black_king_side, false);
            }
            break;
        case WKing:
            if(can_white_castle()) {
                copy_castling_rights();
                set_white_castling_rights(false);
                if(mf == King_Side_Castle)       { brd[h1] = Empty; brd[f1] = WRook; }
                else if(mf == Queen_Side_Castle) { brd[a1] = Empty; brd[d1] = WRook; }
            }
            break;
        case BKing:
            if(can_black_castle()) {
                copy_castling_rights();
                set_black_castling_rights(false);
                if(mf == King_Side_Castle)       { brd[h8] = Empty; brd[f8] = BRook; }
                else if(mf == Queen_Side_Castle) { brd[a8] = Empty; brd[d8] = BRook; }
            }
            break;
        default:
            break;
        }

        if(m.is_promotion()) {
            switch (mf) {
            case Queen_Promotion:
            case Queen_Promotion_Capture:
                side_to_move == White ? brd[to] = WQueen : brd[to] = BQueen;
                break;
            case Knight_Promotion:
            case Knight_Promotion_Capture:
                side_to_move == White ? brd[to] = WKnight : brd[to] = BKnight;
                break;
            case Rook_Promotion:
            case Rook_Promotion_Capture:
                side_to_move == White ? brd[to] = WRook : brd[to] = BRook;
                break;
            case Bishop_Promotion:
            case Bishop_Promotion_Capture:
                side_to_move == White ? brd[to] = WBishop : brd[to] = BBishop;
                break;
            default:
                std::cerr << "Make move - promotion move error" << std::endl;
                break;
            }
        }
        else {
            brd[to] = brd[from];
        }

        // set the position of current piece to Empty
        brd[from] = Empty;

        // side to move and move counter
        if(side_to_move == White) {
            side_to_move = Black;
        }
        else {
            side_to_move = White;
            ++move_counter;
        }
    }

    void unmake_move(const Move& m) {

        Move_flag mf {m.get_flag()};
        std::uint8_t from {m.get_from()}, to{m.get_to()};

        // update half_move_counter
        current_half_move_counter = previous_half_move_counter;

        // side to move and move counter
        if(side_to_move == White) {
            side_to_move = Black;
            --move_counter;
        }
        else {
            side_to_move = White;
        }

        // en passant square
        if(mf == Double_Pawn_Push) en_passant_square = Invalid_square;
        else if(mf == En_Passant_Capture) en_passant_square = to;

        // restore castling rights
        switch (brd[from]) {
        case WRook:
            if((from == a1 && could_white_castle_queen_side()) || (from == h1 && could_white_castle_king_side()))
                restore_castling_rights();
            break;
        case BRook:
            if((from == a8 && could_black_castle_queen_side()) || (from == h8 && could_black_castle_king_side()))
                restore_castling_rights();
            break;
        case WKing:
            if(could_white_castle()) {
                restore_castling_rights();
                if(mf == King_Side_Castle)       { brd[h1] = WRook; brd[f1] = Empty; }
                else if(mf == Queen_Side_Castle) { brd[a1] = WRook; brd[d1] = Empty; }
            }
            break;
        case BKing:
            if(could_black_castle()) {
                restore_castling_rights();
                if(mf == King_Side_Castle)       { brd[h8] = BRook; brd[f8] = Empty; }
                else if(mf == Queen_Side_Castle) { brd[a8] = BRook; brd[d8] = Empty; }
            }
            break;
        default:
            break;
        }



        if(m.get_flag() == King_Side_Castle) {

            brd[m.get_from()] = brd[m.get_to()];
            brd[m.get_to()] = Empty;

            if(side_to_move == White) {
                brd[h1] = WRook;
                brd[f1] = Empty;
            }
            else {
                brd[h8] = BRook;
                brd[f8] = Empty;
            }
        }

        if(m.get_flag() == Queen_Side_Castle) {

            brd[m.get_from()] = brd[m.get_to()];
            brd[m.get_to()] = Empty;

            if(side_to_move == White) {
                brd[a1] = WRook;
                brd[d1] = Empty;
            }
            else {
                brd[a8] = BRook;
                brd[d8] = Empty;
            }
        }

        if(m.get_flag() == Capture) {

            brd[m.get_from()] = brd[m.get_to()];
            brd[m.get_to()] = captured;
            captured = Empty;
        }

        if(m.get_flag() == En_Passant_Capture) {
            brd[m.get_from()] = brd[m.get_to()];
            brd[m.get_to()] = Empty;
            en_passant_square = m.get_to();
            side_to_move == White ? brd[en_passant_square - 8] = BPawn : brd[en_passant_square + 8] = WPawn;
        }

        if(m.get_flag() == Queen_Promotion) {
            brd[m.get_from()] = (side_to_move == White ? WPawn : BPawn);
            brd[m.get_to()] = Empty;

        }

        if(m.get_flag() == Rook_Promotion) {
            brd[m.get_from()] = (side_to_move == White ? WPawn : BPawn);
            brd[m.get_to()] = Empty;
        }

        if(m.get_flag() == Knight_Promotion) {
            brd[m.get_from()] = (side_to_move == White ? WPawn : BPawn);
            brd[m.get_to()] = Empty;
        }

        if(m.get_flag() == Bishop_Promotion) {
            brd[m.get_from()] = (side_to_move == White ? WPawn : BPawn);
            brd[m.get_to()] = Empty;
        }

        if(m.get_flag() == Queen_Promotion_Capture) {
            brd[m.get_from()] = (side_to_move == White ? WPawn : BPawn);
            brd[m.get_to()] = captured;
        }

        if(m.get_flag() == Rook_Promotion_Capture) {
            brd[m.get_from()] = (side_to_move == White ? WPawn : BPawn);
            brd[m.get_to()] = captured;
        }

        if(m.get_flag() == Knight_Promotion_Capture) {
            brd[m.get_from()] = (side_to_move == White ? WPawn : BPawn);
            brd[m.get_to()] = captured;
        }

        if(m.get_flag() == Bishop_Promotion_Capture) {
            brd[m.get_from()] = (side_to_move == White ? WPawn : BPawn);
            brd[m.get_to()] = captured;
        }
    }

    bool operator==(const Board& rhs) const {

        // check the piece locations
        for(int i = 0; i <64; ++i)
            if(brd[i] != rhs.brd[i])
                return false;

        // check the move counter
        if(move_counter != rhs.move_counter)
            return false;

        // check half move counter
        if(current_half_move_counter != rhs.current_half_move_counter)
            return false;

        // check the castling rights
        if((castling_rights & 0x0F) != (rhs.castling_rights & 0x0F))
            return false;

        // check en passant sqaure
        if(en_passant_square != rhs.en_passant_square)
            return false;

        // check side to move
        if(side_to_move != rhs.side_to_move)
            return false;

        return true;
    }

    std::string to_FEN() const {

        std::ostringstream fen{""};

        // Field-1: Piece placement
        std::uint8_t empty_counter{0};
        for(int i = 0; i < 64; ++i) {
            if(i > 0 && i % 8 == 0) {
                if(empty_counter!=0) {
                    fen << static_cast<int>(empty_counter);
                    empty_counter = 0;
                }
                fen << '/';
            }
            if(brd[square_visit_order[i]] == Empty) {
                ++empty_counter;
            }
            else {
                if(empty_counter != 0) {
                    fen << static_cast<int>(empty_counter);
                    empty_counter = 0;
                }
                fen << piece_to_char(brd[square_visit_order[i]]);
            }
        }
        if(empty_counter != 0)
            fen << static_cast<int>(empty_counter);

        // Field-2: Active color
        side_to_move == White ? fen << " w " : fen << " b ";

        // Field-3: Castling Availability
        bool flag{true};
        if(query_castling_rights(White_king_side)) {
            flag = false;
            fen << 'K';
        }
        if(query_castling_rights(White_queen_side)) {
            flag = false;
            fen << 'Q';
        }
        if(query_castling_rights(Black_king_side)) {
            flag = false;
            fen << 'k';
        }
        if(query_castling_rights(Black_queen_side)) {
            flag = false;
            fen << 'q';
        }
        if(flag) fen << '-';

        // Field-4: En Passant Square
        fen << ' ' << square_to_string[en_passant_square] << ' ';

        // Field-5: Half Move Clock
        fen << static_cast<int>(current_half_move_counter) << ' ';

        // Field-6: Full Move Number
        fen << move_counter;

        return fen.str();
    }

    void print_board(bool extended = false) const {

        for(int i = 0; i < 64; ++i) {
            if(i > 0 && i % 8 == 0)
                std::cout << std::endl;
            std::cout << piece_to_char(brd[square_visit_order[i]]) << " ";
        }
        std::cout << std::endl;

        if(extended) {
            std::cout << "side to move     : " << side_to_move << std::endl;
            std::cout << "move counter     : " << move_counter << std::endl;
            std::cout << "half move counter: " << static_cast<int>(current_half_move_counter) << std::endl;
            std::cout << "capture_piece    : " << piece_to_char(captured) << std::endl;
            std::cout << "en passant square: " << square_to_string[en_passant_square] << std::endl;
            std::cout << "K                : " << query_castling_rights(White_king_side) << std::endl;
            std::cout << "Q                : " << query_castling_rights(White_queen_side) << std::endl;
            std::cout << "k                : " << query_castling_rights(Black_king_side) << std::endl;
            std::cout << "q                : " << query_castling_rights(Black_queen_side) << std::endl;
        }

        std::cout << "---------------------------------------" << std::endl;
    }

private:
    inline void copy_castling_rights()                { castling_rights |= ((castling_rights & 0x0F) << 4); }
    inline void restore_castling_rights()             { castling_rights |= ((castling_rights & 0xF0) >> 4); }
    inline void set_white_castling_rights(bool flag)  { flag ? (castling_rights |= 3) : (castling_rights &= 0xFC); }
    inline void set_black_castling_rights(bool flag)  { flag ? (castling_rights |= 12) : (castling_rights &= 0xF3); }
    inline bool can_white_castle() const              { return (flag & 0x03); }
    inline bool could_white_castle() const            { return (flag & 0x3F); }
    inline bool can_black_castle() const              { return (flag & 0x0C); }
    inline bool could_black_castle() const            { return (flag & 0xCF); }
    inline bool can_white_castle_king_side() const    { return (flag & 0x01); }
    inline bool can_white_castle_queen_side() const   { return (flag & 0x02); }
    inline bool can_black_castle_king_side() const    { return (flag & 0x04); }
    inline bool can_black_castle_queen_side() const   { return (flag & 0x08); }
    inline bool could_white_castle_king_side() const  { return (flag & 0x10); }
    inline bool could_white_castle_queen_side() const { return (flag & 0x20); }
    inline bool could_black_castle_king_side() const  { return (flag & 0x40); }
    inline bool could_black_castle_queen_side() const { return (flag & 0x80); }
};

class move_generator {
public:

private:

    void generate_white_moves(const Board& b, std::vector<Move>& moves) {

        for(int i = 0; i < 64; ++i) {
            if(b.brd[i] > 0) {
                switch (b.brd[i]) {
                case WPawn:
                    break;
                case WRook:
                    break;
                case WKnight:
                    break;
                case WBishop:
                    break;
                case WQueen:
                    break;
                case WKing:
                    break;
                default:
                    break;
                }
            }
        }
    }
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
        if(fields[1] == "w") b.side_to_move = White;
        else b.side_to_move = Black;

        // Field-3: Castling Availability
        for(int i = 0; i < fields[2].length(); ++i) {
            switch (fields[2][i]) {
            case 'K': b.set_castling_rights(White_king_side, true); break;
            case 'Q': b.set_castling_rights(White_queen_side, true); break;
            case 'k': b.set_castling_rights(Black_king_side, true); break;
            case 'q': b.set_castling_rights(Black_king_side, true); break;
            case '-': break;
            default: std::cerr << "Castling rightd error" << std::endl; break;
            }
        }

        // Field-4: En Passant Square
        (fields[3] == "-") ? b.en_passant_square = Invalid_square : b.en_passant_square = static_cast<Square>(sq(fields[3][1] - '1', fields[3][0] - 'a'));

        // Field-5: Half Move Clock
        b.current_half_move_counter = static_cast<std::uint8_t>(std::stoi(fields[4]));

        // Field-6: Full Move Number
        b.move_counter = static_cast<uint16_t>(std::stoi(fields[5]));
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

    Move_flag arr[14] = {

        Quite,
        Double_Pawn_Push,           // 1
        King_Side_Castle,           // 2
        Queen_Side_Castle,          // 3
        Capture,                    // 4
        En_Passant_Capture,         // 5
        Knight_Promotion,
        Bishop_Promotion,           // 9
        Rook_Promotion,             // 10
        Queen_Promotion,            // 11
        Knight_Promotion_Capture,   // 12
        Bishop_Promotion_Capture,   // 13
        Rook_Promotion_Capture,     // 14
        Queen_Promotion_Capture     // 15
    };

    Board b;
    Move m(b1, c3, arr[0]);
    b.make_move(m);
    b.print_board(true);
    b.unmake_move(m);
    b.print_board(true);


    return 0;
}
