#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <map>
#include <signal.h>
#include <stdlib.h>
#include <execinfo.h>
#include <unistd.h>

#include "game.h"

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

enum class NodeValue {
    terminal_value = 1,
    one,
    num_ships_in_move,
    planet_dest_is_mine,
    planet_dest_is_neutral,
    planet_dest_is_enemy,
    distance_source_dest,
    growth_source,
    growth_dest,
    source_num_ships,
    dest_num_ships,
    enemy_ships_headed_to_source,
    avg_enemy_ships_headed_to_source_dist,
    avg_enemy_ships_headed_to_source_turns_left,
    enemy_ships_headed_to_dest,
    avg_enemy_ships_headed_to_dest_dist,
    avg_enemy_ships_headed_to_dest_turns_left,
    my_ships_headed_to_source,
    avg_my_ships_headed_to_source_dist,
    avg_my_ships_headed_to_source_turns_left,
    my_ships_headed_to_dest,
    avg_my_ships_headed_to_dest_dist,
    avg_my_ships_headed_to_dest_turns_left,
    in_four_growth_source,
    in_four_planets_source,
    in_four_growth_dest,
    in_four_planets_dest,
    in_nine_growth_source,
    in_nine_planets_source,
    in_nine_growth_dest,
    in_nine_planets_dest,
    in_four_my_ships_source,
    in_four_my_ships_dest,
    in_four_enemy_ships_source,
    in_four_enemy_ships_dest,
    in_nine_my_ships_source,
    in_nine_my_ships_dest,
    in_nine_enemy_ships_source,
    in_nine_enemy_ships_dest,
    num_my_planets,
    num_enemy_planets,
    num_neutral_planets,
    total_enemy_ships,
    enemy_ships_on_planets,
    enemy_ships_in_fleets,
    total_my_ships,
    my_ships_on_planets,
    my_ships_in_fleets,
    total_neutral_ships,
    avg_move_distance,
    avg_my_growth,
    avg_enemy_growth,
    aeds,
    aedd,
    operator_value,
    maximum,
    minimum,
    invert_subtract,
    negative_add,
    invert_divide,
    negative_multiply,
    less_than,
    greater_than,
    plus,
    minus,
    multiply,
    safe_divide,
    and_op,
    xor_op,
    nand,
    or_op,
    iflr,
    ifrl,
    end_value
};

static NodeValue StringToEnum(std::string string_val) {
    if (string_val == "1")
        return NodeValue::one;
    if (string_val == "nsim")
        return NodeValue::num_ships_in_move;
    if (string_val == "pdim")
        return NodeValue::planet_dest_is_mine;
    if (string_val == "pdin")
        return NodeValue::planet_dest_is_neutral;
    if (string_val == "pdie")
        return NodeValue::planet_dest_is_enemy;
    if (string_val == "dsd")
        return NodeValue::distance_source_dest;
    if (string_val == "gs")
        return NodeValue::growth_source;
    if (string_val == "gd")
        return NodeValue::growth_dest;
    if (string_val == "sns")
        return NodeValue::source_num_ships;
    if (string_val == "dns")
        return NodeValue::dest_num_ships;
    if (string_val == "nmp")
        return NodeValue::num_my_planets;
    if (string_val == "nep")
        return NodeValue::num_enemy_planets;
    if (string_val == "nnp")
        return NodeValue::num_neutral_planets;
    if (string_val == "tes")
        return NodeValue::total_enemy_ships;
    if (string_val == "eson")
        return NodeValue::enemy_ships_on_planets;
    if (string_val == "esin")
        return NodeValue::enemy_ships_in_fleets;
    if (string_val == "tms")
        return NodeValue::total_my_ships;
    if (string_val == "mson")
        return NodeValue::my_ships_on_planets;
    if (string_val == "msin")
        return NodeValue::my_ships_in_fleets;
    if (string_val == "tns")
        return NodeValue::total_neutral_ships;
    if (string_val == "amd")
        return NodeValue::avg_move_distance;
    if (string_val == "amg")
        return NodeValue::avg_my_growth;
    if (string_val == "aeg")
        return NodeValue::avg_enemy_growth;
    if (string_val == "enshs")
        return NodeValue::enemy_ships_headed_to_source;
    if (string_val == "enshd")
        return NodeValue::enemy_ships_headed_to_dest;
    if (string_val == "mshs")
        return NodeValue::my_ships_headed_to_source;
    if (string_val == "mshd")
        return NodeValue::my_ships_headed_to_dest;
    if (string_val == "aeshsd")
        return NodeValue::avg_enemy_ships_headed_to_source_dist;
    if (string_val == "aeshst")
        return NodeValue::avg_enemy_ships_headed_to_source_turns_left;
    if (string_val == "aeshdd")
        return NodeValue::avg_enemy_ships_headed_to_dest_dist;
    if (string_val == "aeshdt")
        return NodeValue::avg_enemy_ships_headed_to_dest_turns_left;
    if (string_val == "amshsd")
        return NodeValue::avg_my_ships_headed_to_source_dist;
    if (string_val == "amshst")
        return NodeValue::avg_my_ships_headed_to_source_turns_left;
    if (string_val == "amshdd")
        return NodeValue::avg_my_ships_headed_to_dest_dist;
    if (string_val == "amshdt")
        return NodeValue::avg_my_ships_headed_to_dest_turns_left;
    if (string_val == "4gs")
        return NodeValue::in_four_growth_source;
    if (string_val == "4ps")
        return NodeValue::in_four_planets_source;
    if (string_val == "4gd")
        return NodeValue::in_four_growth_dest;
    if (string_val == "4pd")
        return NodeValue::in_four_planets_dest;
    if (string_val == "9gs")
        return NodeValue::in_nine_growth_source;
    if (string_val == "9ps")
        return NodeValue::in_nine_planets_source;
    if (string_val == "9gd")
        return NodeValue::in_nine_growth_dest;
    if (string_val == "9pd")
        return NodeValue::in_nine_planets_dest;
    if (string_val == "i4mss")
        return NodeValue::in_four_my_ships_source;
    if (string_val == "i4msd")
        return NodeValue::in_four_my_ships_dest;
    if (string_val == "i4ess")
        return NodeValue::in_four_enemy_ships_source;
    if (string_val == "i4esd")
        return NodeValue::in_four_enemy_ships_dest;
    if (string_val == "i9mss")
        return NodeValue::in_nine_my_ships_source;
    if (string_val == "i9msd")
        return NodeValue::in_nine_my_ships_dest;
    if (string_val == "i9ess")
        return NodeValue::in_nine_enemy_ships_source;
    if (string_val == "i9esd")
        return NodeValue::in_nine_enemy_ships_dest;
    if (string_val == "aeds")
        return NodeValue::aeds;
    if (string_val == "aedd")
        return NodeValue::aedd;
    if (string_val == "max")
        return NodeValue::maximum;
    if (string_val == "min")
        return NodeValue::minimum;
    if (string_val == "invs")
        return NodeValue::invert_subtract;
    if (string_val == "nega")
        return NodeValue::negative_add;
    if (string_val == "invd")
        return NodeValue::invert_divide;
    if (string_val == "negm")
        return NodeValue::negative_multiply;
    if (string_val == "lt")
        return NodeValue::less_than;
    if (string_val == "gt")
        return NodeValue::greater_than;
    if (string_val == "plus")
        return NodeValue::plus;
    if (string_val == "minus")
        return NodeValue::minus;
    if (string_val == "times")
        return NodeValue::multiply;
    if (string_val == "div")
        return NodeValue::safe_divide;
    if (string_val == "and_op")
        return NodeValue::and_op;
    if (string_val == "xor")
        return NodeValue::xor_op;
    if (string_val == "nand")
        return NodeValue::nand;
    if (string_val == "or_op")
        return NodeValue::or_op;

    if (string_val == "iflr")
        return NodeValue::iflr;

    if (string_val == "ifrl")
        return NodeValue::ifrl;

    exit(1);
    return NodeValue::terminal_value;
}

struct GeneticTree {
public:
	GeneticTree(
    std::unique_ptr<GeneticTree> left,
    std::unique_ptr<GeneticTree> right,
	NodeValue value,
    bool is_terminal) :
	left(std::move(left)),
	right(std::move(right)),
	is_terminal(is_terminal),
	value(value) {}

    std::unique_ptr<GeneticTree> left;
    std::unique_ptr<GeneticTree> right;
    bool is_terminal;
	NodeValue value;
};



static std::vector<std::string> FindSubTreesAndValue(std::string string_representation) {
    size_t current_index = 1;
    int count_of_open_parens = 1;
    while (count_of_open_parens > 0 && current_index < string_representation.length()) {
        if (string_representation[current_index] == '{')
            count_of_open_parens += 1;
        if (string_representation[current_index] == '}')
            count_of_open_parens -= 1;
        current_index += 1;
        if (count_of_open_parens == 0)
            break;
    }

    if (count_of_open_parens > 0) {
        std::cout<<"count of parens";
        exit(1);
        return std::vector<std::string>();
    }

    if (string_representation[current_index] != ',') {
        std::cout<<"commas";
        exit(1);
        return std::vector<std::string>();
    }

    size_t index_of_second_comma = string_representation.substr(current_index+1,string_representation.length() - current_index - 1).find(',') + current_index+1;

    std::vector<std::string> lrv;
    lrv.push_back(string_representation.substr(0,current_index));
    lrv.push_back(string_representation.substr(index_of_second_comma +      1,
                                  string_representation.length() - index_of_second_comma -1));
    lrv.push_back(string_representation.substr(current_index+1,index_of_second_comma-current_index-1));

    return lrv;
}


static std::unique_ptr<GeneticTree> DecodeToGeneticTree(std::string string_representation) {
    std::cout<<string_representation<<"\n";
    while (string_representation[string_representation.size()-1] != '}')
        string_representation = string_representation.substr(0, string_representation.size()-1);
    if (string_representation == "{}")
        return nullptr;
    if (string_representation[0] != '{' or \
            string_representation[string_representation.length()-1] != '}') {
        exit(1);
    	return nullptr;
    }

    std::cout<<"find sub";

    std::vector<std::string> lrv = FindSubTreesAndValue(
        string_representation.substr(1,string_representation.length()-2));

    for (auto i : lrv) {
        std::cout<<i<<"\n";
    }


    return std::make_unique<GeneticTree>(DecodeToGeneticTree(lrv[0]),
                       DecodeToGeneticTree(lrv[1]), StringToEnum(lrv[2]),
                       lrv[0] == "{}");

}


struct ExtraState {
public:
        size_t total_enemy_ships = 0;
        size_t total_my_ships = 0;
        size_t total_neutral_ships = 0;
        size_t enemy_ships_on_planets = 0;
        size_t enemy_ships_in_fleets = 0;
        size_t my_ships_on_planets = 0;
        size_t my_ships_in_fleets = 0;

        float avg_move_distance = 0.0f;
        float avg_my_growth = 0.0f;
        float avg_enemy_growth = 0.0f;
        std::map<int, int> enemy_ships_headed_to_planet;
        std::map<int, int> my_ships_headed_to_planet;

        std::map<int, float> avg_enemy_ships_headed_to_planet_distance;
        std::map<int, float> avg_enemy_ships_headed_to_planet_turns_left;
        std::map<int, float> avg_my_ships_headed_to_planet_distance;
        std::map<int, float> avg_my_ships_headed_to_planet_turns_left;

        std::map<int, float> in_four_growth;
        std::map<int, float> in_four_planets;
        std::map<int, float> in_four_my_ships;
        std::map<int, float> in_four_enemy_ships;
        std::map<int, float> in_nine_growth;
        std::map<int, float> in_nine_planets;
        std::map<int, float> in_nine_my_ships;
        std::map<int, float> in_nine_enemy_ships;

        std::map<int, float> average_enemy_distance;
};


struct Move {
public:
    Move(Planet& source, Planet& destination, int num_ships): source(source), destination(destination), num_ships(num_ships){}
        Planet source;
        Planet destination;
        int num_ships;
};


float ScoreState(Game&  pw, Move& move, ExtraState& es, GeneticTree* tree) {
    NodeValue value = tree->value;
    Planet& dest = move.destination;
    Planet& source = move.source;
    GeneticTree* left = tree->left.get();
    GeneticTree* right = tree->right.get();
    float bottom = 0.0f;
    float top = 0.0f;

    switch (value) {
    case NodeValue::one:
        return 1.0f;
    case NodeValue::num_ships_in_move:
        return move.num_ships;
    case NodeValue::planet_dest_is_mine:
        return dest.owner == 1 ? 1.0f : 0.0f;
    case NodeValue::planet_dest_is_neutral:
        return dest.owner == 0 ? 1.0f : 0.0f;
    case NodeValue::planet_dest_is_enemy:
        return dest.owner > 1 ? 1.0f : 0.0f;
    case NodeValue::distance_source_dest:
        return pw.desc.Distance(source.planetId, dest.planetId);
    case NodeValue::growth_source:
        return source.growthRate;
    case NodeValue::growth_dest:
        return dest.growthRate;
    case NodeValue::source_num_ships:
        return pw.GetPlanet(source.planetId).numShips;
    case NodeValue::dest_num_ships:
        return pw.GetPlanet(dest.planetId).numShips;
    case NodeValue::num_my_planets:
        return pw.MyPlanets().size();
    case NodeValue::num_enemy_planets:
        return pw.EnemyPlanets().size();
    case NodeValue::num_neutral_planets:
        return pw.NeutralPlanets().size();
    case NodeValue::total_enemy_ships:
        return es.total_enemy_ships ;
    case NodeValue::enemy_ships_on_planets:
        return es.enemy_ships_on_planets ;
    case NodeValue::enemy_ships_in_fleets:
        return es.enemy_ships_in_fleets ;
    case NodeValue::total_my_ships:
        return es.total_my_ships ;
    case NodeValue::my_ships_on_planets:
        return es.my_ships_on_planets ;
    case NodeValue::my_ships_in_fleets:
        return es.my_ships_in_fleets ;
    case NodeValue::total_neutral_ships:
        return es.total_neutral_ships ;
    case NodeValue::avg_move_distance:
        return es.avg_move_distance ;
    case NodeValue::avg_my_growth:
        return es.avg_my_growth ;
    case NodeValue::avg_enemy_growth:
        return es.avg_enemy_growth ;
    case NodeValue::enemy_ships_headed_to_source:
        return es.enemy_ships_headed_to_planet[source.planetId] ;
    case NodeValue::enemy_ships_headed_to_dest:
        return es.enemy_ships_headed_to_planet[dest.planetId] ;
    case NodeValue::my_ships_headed_to_source:
        return es.my_ships_headed_to_planet[source.planetId] ;
    case NodeValue::my_ships_headed_to_dest:
        return es.my_ships_headed_to_planet[dest.planetId] ;

    case NodeValue::avg_enemy_ships_headed_to_source_dist:
        return es.avg_enemy_ships_headed_to_planet_distance[source.planetId] ;
    case NodeValue::avg_enemy_ships_headed_to_source_turns_left:
        return es.avg_enemy_ships_headed_to_planet_turns_left[source.planetId] ;
    case NodeValue::avg_enemy_ships_headed_to_dest_dist:
        return es.avg_enemy_ships_headed_to_planet_distance[dest.planetId] ;
    case NodeValue::avg_enemy_ships_headed_to_dest_turns_left:
        return es.avg_enemy_ships_headed_to_planet_turns_left[dest.planetId] ;

    case NodeValue::avg_my_ships_headed_to_source_dist:
        return es.avg_my_ships_headed_to_planet_distance[source.planetId] ;
    case NodeValue::avg_my_ships_headed_to_source_turns_left:
        return es.avg_my_ships_headed_to_planet_turns_left[source.planetId] ;
    case NodeValue::avg_my_ships_headed_to_dest_dist:
        return es.avg_my_ships_headed_to_planet_distance[dest.planetId] ;
    case NodeValue::avg_my_ships_headed_to_dest_turns_left:
        return es.avg_my_ships_headed_to_planet_turns_left[dest.planetId] ;

    case NodeValue::in_four_growth_source:
        return es.in_four_growth[source.planetId] ;
    case NodeValue::in_four_planets_source:
        return es.in_four_planets[source.planetId] ;
    case NodeValue::in_four_growth_dest:
        return es.in_four_growth[dest.planetId] ;
    case NodeValue::in_four_planets_dest:
        return es.in_four_planets[dest.planetId] ;

    case NodeValue::in_four_my_ships_source:
        return es.in_four_my_ships[source.planetId] ;
    case NodeValue::in_four_my_ships_dest:
        return es.in_four_my_ships[dest.planetId] ;
    case NodeValue::in_four_enemy_ships_source:
        return es.in_four_enemy_ships[source.planetId] ;
    case NodeValue::in_four_enemy_ships_dest:
        return es.in_four_enemy_ships[dest.planetId] ;

    case NodeValue::in_nine_growth_source:
        return es.in_nine_growth[source.planetId] ;
    case NodeValue::in_nine_planets_source:
        return es.in_nine_planets[source.planetId] ;
    case NodeValue::in_nine_growth_dest:
        return es.in_nine_growth[dest.planetId] ;
    case NodeValue::in_nine_planets_dest:
        return es.in_nine_planets[dest.planetId] ;

    case NodeValue::in_nine_my_ships_source:
        return es.in_nine_my_ships[source.planetId] ;
    case NodeValue::in_nine_my_ships_dest:
        return es.in_nine_my_ships[dest.planetId] ;
    case NodeValue::in_nine_enemy_ships_source:
        return es.in_nine_enemy_ships[source.planetId] ;
    case NodeValue::in_nine_enemy_ships_dest:
        return es.in_nine_enemy_ships[dest.planetId] ;

    case NodeValue::aeds:
        return es.average_enemy_distance[source.planetId];

    case NodeValue::aedd:
        return es.average_enemy_distance[dest.planetId];

    case NodeValue::maximum:
        return std::max(ScoreState(pw, move, es,left),
                   ScoreState(pw, move, es,right));
    case NodeValue::minimum:
        return std::min(ScoreState(pw, move, es,left),
                   ScoreState(pw, move, es,right));
    case NodeValue::invert_subtract:
        return ScoreState(pw, move, es,right) - 
            ScoreState(pw, move, es,left);
    case NodeValue::negative_add:
        return -1.0f * ScoreState(pw, move, es,left) - 
             ScoreState(pw, move, es,right);
    case NodeValue::invert_divide:
    
        bottom = ScoreState(pw, move, es,left) ;
        if (bottom < 0.0000001f && bottom > -0.0000001f)
            return 0.0f;
        top = ScoreState(pw, move, es,right) ;
        return  top/bottom;
    
    case NodeValue::negative_multiply:
        return -1.0f * ScoreState(pw, move, es,right) * 
            ScoreState(pw, move, es,left);
    case NodeValue::less_than:
        return ScoreState(pw, move, es,left) < ScoreState(pw, move, es,right) ? 1.0f : 0.0f;
    case NodeValue::greater_than:
        return ScoreState(pw, move, es,left) > ScoreState(pw, move, es,right) ? 1.0f : 0.0f;
    case NodeValue::plus:
        return ScoreState(pw, move, es,left) + 
            ScoreState(pw, move, es,right);
    case NodeValue::minus:
        return ScoreState(pw, move, es,left) - 
            ScoreState(pw, move, es,right);
    case NodeValue::multiply:
        return ScoreState(pw, move, es,left) * 
            ScoreState(pw, move, es,right);
    case NodeValue::safe_divide:
    
        bottom = ScoreState(pw, move, es,right);
        if (bottom< 0.0000001f && bottom > -0.0000001f)
            return 0.0f;
        top = ScoreState(pw, move, es,left) ;
        return  top/bottom;
      
    case NodeValue::and_op:
        return  ScoreState(pw, move, es,left) > 0.000000001f &&
            ScoreState(pw, move, es,right) > 0.000000001f ? 1.0f : 0.0f;
    case NodeValue::xor_op:
        return  ((ScoreState(pw, move, es,left) > 0.000000001f) !=
            (ScoreState(pw, move, es,right) > 0.000000001f)) ? 1.0f : 0.0f;
    case NodeValue::nand:
        return  !(ScoreState(pw, move, es,left) > 0.000000001f &&
            ScoreState(pw, move, es,right) > 0.000000001f) ? 1.0f : 0.0f;
    case NodeValue::or_op:
        return  ScoreState(pw, move, es,left) > 0.000000001f ||
            ScoreState(pw, move, es,right) > 0.000000001f ? 1.0f : 0.0f;
    case NodeValue::iflr:
        return (ScoreState(pw, move, es,left) > 0.000000001f) ? ScoreState(pw, move, es,right) : 0.0f;
    case NodeValue::ifrl:
        return ScoreState(pw, move, es,right) > 0.000000001f ? ScoreState(pw, move, es,left) : 0.0f;
    default:
        exit(1);
        return 0.0f;
    }
    return 0.0f;

}

static std::pair<std::vector<Move>, ExtraState> GetAllPossibleMoves(Game& planet_wars) {
    std::vector<Move> moves;
    ExtraState extra_state;

    for (const Fleet& f : planet_wars.Fleets()) {
        if (f.owner == 1) {
            extra_state.avg_my_ships_headed_to_planet_distance[f.destinationPlanet] += f.numShips * f.totalTripLength;
            extra_state.avg_my_ships_headed_to_planet_turns_left[f.destinationPlanet] += f.numShips * f.turnsRemaining;
            extra_state.my_ships_headed_to_planet[f.destinationPlanet] += f.numShips;
            extra_state.total_my_ships += f.numShips;
            extra_state.my_ships_in_fleets += f.numShips;
        }
        else {
            extra_state.avg_enemy_ships_headed_to_planet_distance[f.destinationPlanet] += f.numShips * f.totalTripLength;
            extra_state.avg_enemy_ships_headed_to_planet_turns_left[f.destinationPlanet] += f.numShips * f.turnsRemaining;
            extra_state.enemy_ships_headed_to_planet[f.destinationPlanet] += f.numShips;
            extra_state.total_enemy_ships += f.numShips;
            extra_state.enemy_ships_in_fleets += f.numShips;
            extra_state.average_enemy_distance[f.destinationPlanet] += f.numShips * f.turnsRemaining;
        }
    }

    for (auto const& item : extra_state.enemy_ships_headed_to_planet) {
        float ships_divisor = std::max(float(item.second), 1.0f);
        extra_state.avg_enemy_ships_headed_to_planet_distance[item.first] /= ships_divisor;
        extra_state.avg_enemy_ships_headed_to_planet_turns_left[item.first] /=  ships_divisor;
    }

    for (auto const& item : extra_state.my_ships_headed_to_planet) {
        float ships_divisor = std::max(float(item.second), 1.0f);
        extra_state.avg_my_ships_headed_to_planet_distance[item.first] /= ships_divisor;
        extra_state.avg_my_ships_headed_to_planet_turns_left[item.first] /=  ships_divisor;
    }

    std::vector<int> enemy_growth;
    for (auto& planet : planet_wars.EnemyPlanets()) {
        extra_state.enemy_ships_on_planets += planet.numShips;
        extra_state.total_enemy_ships += planet.numShips;
        enemy_growth.push_back(planet.growthRate);
    }

    for (auto growth : enemy_growth)
        extra_state.avg_enemy_growth += float(growth)/enemy_growth.size();

    for (auto& planet : planet_wars.NeutralPlanets())
        extra_state.total_neutral_ships += planet.numShips;

    std::vector<int> move_distances;
    std::vector<int> my_growth;

    for (auto& planet_source : planet_wars.MyPlanets()) {
        my_growth.push_back(planet_source.growthRate);
        extra_state.my_ships_on_planets += planet_source.numShips;
        extra_state.total_my_ships += planet_source.numShips;
        for (auto& planet_dest : planet_wars.Planets()) {
            if (planet_source.planetId == planet_dest.planetId)
                continue;
            move_distances.push_back(
                planet_wars.desc.Distance(planet_source.planetId, planet_dest.planetId));
            int send_ships = 0;
            moves.push_back(Move(planet_source, planet_dest, send_ships));
        }
    }

    for (auto& planet_a : planet_wars.Planets()) {
        for (auto& planet_b : planet_wars.Planets()) {
            if (planet_b.owner > 1) {
                extra_state.average_enemy_distance[planet_a.planetId] += planet_b.numShips * planet_wars.desc.Distance(planet_a.planetId, planet_b.planetId);
            }
            int distance = planet_wars.desc.Distance(planet_a.planetId, planet_b.planetId);
            if (distance > 9)
                continue;
            extra_state.in_nine_growth[planet_a.planetId] += planet_b.growthRate;
            extra_state.in_nine_planets[planet_a.planetId] += 1;
            extra_state.in_nine_my_ships[planet_a.planetId] += planet_b.owner == 1 ? planet_b.numShips : 0;
            extra_state.in_nine_enemy_ships[planet_a.planetId] += planet_b.owner > 1 ? planet_b.numShips : 0;
            if (distance > 4)
                continue;
            extra_state.in_four_growth[planet_a.planetId] += planet_b.growthRate;
            extra_state.in_four_planets[planet_a.planetId] += 1;
            extra_state.in_four_my_ships[planet_a.planetId] += planet_b.owner == 1 ? planet_b.numShips : 0;
            extra_state.in_four_enemy_ships[planet_a.planetId] += planet_b.owner > 1 ? planet_b.numShips : 0;
        }
    }

    for (int distance : move_distances)
        extra_state.avg_move_distance += float(distance)/move_distances.size();

    for (auto growth : my_growth)
        extra_state.avg_my_growth += float(growth)/my_growth.size();

    for (auto planetId : extra_state.average_enemy_distance) {
      extra_state.average_enemy_distance[planetId.first] = extra_state.average_enemy_distance[planetId.first] / extra_state.total_enemy_ships;
    }

    return std::make_pair(moves,extra_state);
}

static float ScoreMove(Game& planet_wars, GeneticTree* tree, Move& move, ExtraState& extra_state) {
    return ScoreState(planet_wars, move, extra_state, tree);
}


static void ScoreMoveUpdateScore(Game& planet_wars, GeneticTree* tree, Move& move, ExtraState& extra_state, std::map<Move*, float>& scores) {
    scores[&move] = ScoreMove(planet_wars, tree, move, extra_state);
}

static int CalculateShipsToSend(Game& planet_wars, GeneticTree* tree, Move& move, ExtraState& extra_state) {
   return std::max(0, std::min(planet_wars.GetPlanet(move.source.planetId).numShips, int(ScoreMove(planet_wars, tree, move, extra_state))));
}


static void DoTurn(Game& pw, GeneticTree* tree, GeneticTree* tree2) {
    int fleets_sent = 0;
    auto possible_moves_and_state = GetAllPossibleMoves(pw);
    std::vector<Move> possible_moves = std::move(possible_moves_and_state.first);
    ExtraState& extra_state = possible_moves_and_state.second;
    if (possible_moves.size() == 0)
        return;
    std::random_shuffle(possible_moves.begin(), possible_moves.end());
    std::map<Move*,float> scores;

    for (auto& move : possible_moves) {
        ScoreMoveUpdateScore(pw, tree, move, extra_state, scores);
    }

    while (scores.size() > 0 && fleets_sent < 100) {
        auto max_item = std::max_element(scores.begin(), scores.end(), [] (auto& lhs, auto& rhs) {return lhs.second < rhs.second;});

        if (max_item->second < 0.00000001f)
            return;

        Move move = *(max_item->first);
        scores.erase(max_item->first);

        float score = ScoreMove(pw, tree, move, extra_state);
        if (score < 0.00000001f)
            continue;

        int ships_to_send = CalculateShipsToSend(pw, tree2, move, extra_state);
        if (ships_to_send == 0)
            continue;
        move.num_ships = ships_to_send;

        fleets_sent += 1;
        pw.IssueOrder(move.source.planetId, move.destination.planetId, move.num_ships);


        extra_state.my_ships_in_fleets += move.num_ships;
        extra_state.my_ships_on_planets -= move.num_ships;

        int distance_weight = pw.desc.Distance(move.source.planetId, move.destination.planetId) * move.num_ships;
        int old_ships = extra_state.my_ships_headed_to_planet[move.destination.planetId];
        int new_ships = old_ships + move.num_ships;

        extra_state.avg_my_ships_headed_to_planet_distance[move.destination.planetId] = float(extra_state.avg_my_ships_headed_to_planet_distance[move.destination.planetId] * old_ships + distance_weight) / new_ships;
        extra_state.avg_my_ships_headed_to_planet_turns_left[move.destination.planetId] = float(extra_state.avg_my_ships_headed_to_planet_turns_left[move.destination.planetId] * old_ships + distance_weight) / new_ships;
        

        extra_state.my_ships_headed_to_planet[move.destination.planetId] += move.num_ships;
    }

}

int main(int argc, char *argv[]) {   
    signal(SIGSEGV, handler);

    std::string line = "{{{{{},dns,{}},iflr,{{{},pdie,{}},xor,{{{},enshd,{}},min,{{},pdin,{}}}}},max,{{{{{},sns,{}},gt,{{{},dns,{}},plus,{{},dns,{}}}},iflr,{{{{{},pdie,{}},xor,{{{},pdin,{}},min,{{{},pdin,{}},times,{{{{{},sns,{}},gt,{{{},dns,{}},plus,{{},dns,{}}}},iflr,{{{{{},4pd,{}},xor,{{{},pdin,{}},min,{{{},pdin,{}},times,{{},pdin,{}}}}},iflr,{{{},gd,{}},div,{{},aeshdt,{}}}},iflr,{{{},gd,{}},div,{{},dsd,{}}}}},max,{{{},nsim,{}},times,{{{},enshd,{}},xor,{{},nsim,{}}}}}}}},xor,{{{},pdin,{}},min,{{},pdin,{}}}},iflr,{{{},gd,{}},div,{{},dsd,{}}}}},max,{{{},nsim,{}},times,{{{{{{},dns,{}},iflr,{{},pdie,{}}},max,{{},pdin,{}}},ifrl,{{{},pdin,{}},minus,{{},enshs,{}}}},xor,{{},nsim,{}}}}}},ifrl,{{{},4pd,{}},minus,{{},enshs,{}}}}";
    std::string line2 = "{{{{{},dns,{}},plus,{{{{},i4esd,{}},times,{{{},sns,{}},minus,{{{},tes,{}},div,{{},nmp,{}}}}},plus,{{{{},mshs,{}},times,{{},pdie,{}}},times,{{},dsd,{}}}}},max,{{{},dns,{}},plus,{{{},aedd,{}},plus,{{{{},mshs,{}},times,{{{},i4esd,{}},times,{{{},mshs,{}},times,{{{{},i4esd,{}},times,{{},i9msd,{}}},plus,{{{},gs,{}},times,{{},aeds,{}}}}}}},times,{{},dsd,{}}}}}},min,{{{{},sns,{}},plus,{{{},dns,{}},times,{{},aedd,{}}}},minus,{{{},i4esd,{}},div,{{},nmp,{}}}}}";

    if (argc > 1) {   // install our handler
      std::fstream myfile;
      if (argv[1] != "")
      myfile.open(argv[1]);
      line = "";
      line2 = "";
      if (myfile.is_open())
    	{
    	  getline (myfile,line);
        getline (myfile,line2);
        myfile.close();
    	}
    }

    std::unique_ptr<GeneticTree> tree = DecodeToGeneticTree(line);
    std::unique_ptr<GeneticTree> tree2 = DecodeToGeneticTree(line2);

	std::string current_line;
	std::string map_data;
	while (true) {
		int c = std::cin.get();
		if(c < 0) break;
		current_line += (char)(unsigned char)c;
		if (c == '\n') {
			if (current_line.length() >= 2 && current_line.substr(0, 2) == "go") {
				Game game;
				game.ParseGameState(map_data);
				map_data = "";
				DoTurn(game, tree.get(), tree2.get());
				game.FinishTurn();
			} else {
				map_data += current_line;
			}
			current_line = "";
		}
	}
	return 0;
}
