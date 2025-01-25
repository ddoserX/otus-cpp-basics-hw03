#pragma once

namespace hw03
{
struct score_data;

bool init_player();

void increase_player_score();

void check_and_record_score(const score_data &);

void check_and_record_score();

void print_score_table();

bool check_save_file_exists();

bool save_score_table();

bool load_score_table();
} // namespace hw03
