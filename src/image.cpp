#include "ceng391/image.hpp"

#include<fstream>
#include<cstring>
#include <iostream>

using namespace std;

namespace ceng391 {

Image::Image(int width, int height, int step, int channels)
{
        m_width = width;
        m_height = height;
        if (step < m_width)
                step = m_width;
        m_step = step;

        switch(channels){
                case 1:
                break;
                case 3:
                break;
                case 4:
                break;
                default:
                cerr << "Provided an invalid channel value!" << endl;
                exit(1);
        }
        m_n_channels = channels;
        
        m_data = new uchar[m_step * m_height * m_n_channels];
}

Image::~Image()
{
        delete [] m_data;
}

void Image::set_rect_grayscale(int x_tl, int y_tl, int width, int height, uchar value)
{

        if (x_tl < 0) {
                width += x_tl;
                x_tl = 0;
        }
        
        if (y_tl < 0) {
                height += y_tl;
                y_tl = 0;
        }

        int length = min(width, m_width - x_tl);
        int y_max = min(y_tl + height, m_height);

        if (m_n_channels == 1) {
                for (int y = y_tl; y < y_max; y++) {
                        uchar* row_y = data(y) + x_tl;
                        for (int x = 0; x < length; x++) {
                                *row_y = value;
                                row_y += m_n_channels;
                        }
                }
        }

        if (m_n_channels == 3) {
                for (int y = y_tl; y < y_max; y++) {
                        uchar* row_y = data(y) + x_tl * m_n_channels;
                        for (int x = 0; x < length; x++) {
                                *row_y = value;
                                *(row_y + 1) = value;
                                *(row_y + 2) = value;
                                row_y += m_n_channels;
                        }
                }
        }

        if (m_n_channels == 4) {
                for (int y = y_tl; y < y_max; y++) {
                        uchar* row_y = data(y) + x_tl * m_n_channels;
                        for(int x = 0; x < length; x++) {
                                *row_y = value;
                                *(row_y + 1) = value;
                                *(row_y + 2) = value;
                                *(row_y + 3) = 255;
                                row_y += m_n_channels;
                        }
                }
        }
}

void Image::set_rect_rgb(int x_tl, int y_tl, int width, int height, uchar* values)
{
        if (x_tl < 0){
                width += x_tl;
                x_tl = 0;
        }

        if (y_tl < 0){
                height += y_tl;
                y_tl = 0;
        }

        int length = min(width, m_width - x_tl);
        int y_max = min(y_tl + height, m_height);

        if (m_n_channels == 1) {
                uchar value = (*values + *(values+1) + *(values+2))/3;
                for (int y = y_tl; y < y_max; y++){
                        uchar* row_y = data(y) + x_tl;
                        for (int x = 0; x < length; x++){
                                *row_y = value;
                                row_y++;
                        }
                }
        }

        if (m_n_channels == 3) {
                for (int y = y_tl; y < y_max; y++) {
                        uchar* row_y = data(y) + x_tl * m_n_channels;
                        for (int x = 0; x < length; x++) {
                                *row_y = *values;
                                *(row_y+1) = *(values+1);
                                *(row_y+2) = *(values+2);
                                row_y += m_n_channels;
                        }
                }
        }

        if (m_n_channels == 4) {
                for (int y = y_tl; y < y_max; y++){
                        uchar* row_y = data(y) + x_tl * m_n_channels;
                        for (int x = 0; x < length; x++) {
                                *row_y = *values;
                                *(row_y+1) = *(values+1);
                                *(row_y+2) = *(values+2);
                                *(row_y+3) = 255;
                                row_y += m_n_channels;
                        }
                }
        }

}

void Image::set_rect_rgba(int x_tl, int y_tl, int width, int height, uchar* values) 
{
        if (x_tl < 0){
                width += x_tl;
                x_tl = 0;
        }

        if (y_tl < 0){
                height += y_tl;
                y_tl = 0;
        }

        int length = min(width, m_width - x_tl);
        int y_max = min(y_tl + height, m_height);
        
        if (m_n_channels == 1) {
                uchar value = (*values + *(values+1) + *(values+2))/3;
                for (int y = y_tl; y < y_max; y++){
                        uchar* row_y = data(y)+ x_tl;
                        for (int x = 0; x < length; x++){
                                *row_y = value;
                                row_y++;
                        }
                }
        }

        if (m_n_channels == 3) {
                for (int y = y_tl; y < y_max; y++) {
                        uchar* row_y = data(y) + x_tl * m_n_channels;
                        for (int x = 0; x < length; x++){
                                *row_y = *values;
                                *(row_y + 1) = *(values + 1);
                                *(row_y + 2) = *(values + 2);
                                row_y += m_n_channels;
                        }
                }
        }

        if (m_n_channels == 4) {
                for (int y = y_tl; y < y_max; y++){
                        uchar* row_y = data(y) + x_tl * m_n_channels;
                        for (int x = 0; x < length; x++) {
                                *row_y = *values;
                                *(row_y + 1) = *(values + 1);
                                *(row_y + 2) = *(values + 2);
                                *(row_y + 3) = *(values + 3);
                                row_y += m_n_channels;
                        }
                }
        }
}

void Image::to_grayscale() 
{
        if (m_n_channels == 1) return;

        else {
                int old_m_n_channels = m_n_channels;
                uchar* old_m_data = data();
                m_n_channels = 1;
                m_data = new uchar[m_step * m_height];         
                for (int y = 0; y < m_height; y++) {
                        uchar* row_y = data(y);
                        uchar* old_row_y = old_m_data + y * m_step * old_m_n_channels;
                        for (int x = 0; x < m_width; x++) {
                                *row_y = (*old_m_data * 0.3) + (*(old_m_data + 1) * 0.59) + (*(old_m_data + 2) * 0.11);
                                row_y += m_n_channels;
                                old_row_y += old_m_n_channels;
                                
                        }

                }
                delete[] old_m_data;
        }

}

void Image::to_rgb()
{
        if (m_n_channels == 3) return;

        if(m_n_channels == 1) {
                int old_m_n_channels = m_n_channels;
                uchar* old_m_data = data();
                m_n_channels = 3;
                m_data = new uchar[m_step * m_height * m_n_channels];
                for (int y = 0; y < m_height; y++) {
                        uchar* row_y = data(y);
                        uchar* old_row_y = old_m_data + y * m_step;
                        for (int x = 0; x < m_width; x++) {
                                *row_y = *old_row_y;
                                *(row_y + 1) = *old_row_y;
                                *(row_y + 2) = *old_row_y;
                                row_y += m_n_channels;
                                old_row_y += old_m_n_channels;
                        }
                }
                delete[] old_m_data;
        }

        if (m_n_channels == 4) {
                int old_m_n_channels = m_n_channels;
                uchar* old_m_data = data();
                m_n_channels = 3;
                m_data = new uchar[m_step * m_height * m_n_channels];
                for (int y = 0; y < m_height; y++) {
                        uchar* row_y = data(y);
                        uchar* old_row_y = old_m_data + y * m_step * old_m_n_channels;
                        for(int x = 0; x < m_width; x++){
                                *row_y = *old_row_y;
                                *(row_y + 1) = *(old_row_y + 1);
                                *(row_y + 2) = *(old_row_y + 2);
                                row_y += m_n_channels;
                                old_row_y += old_m_n_channels;

                        }
                }
                delete[] old_m_data;
        }
}

void Image::to_rgba()
{
        if (m_n_channels == 4) return;

        if (m_n_channels == 1) {
                int old_m_n_channels = m_n_channels;
                uchar* old_m_data = data();
                m_n_channels = 4;
                m_data = new uchar[m_step * m_height * m_n_channels];
                for (int y = 0; y < m_height; y++) {
                        uchar* row_y = data(y);
                        uchar* old_row_y = old_m_data + y * m_step;
                        for (int x = 0; x < m_width; x++) {
                                *row_y = *old_row_y;
                                *(row_y + 1) = *old_row_y;
                                *(row_y + 2) = *old_row_y;
                                *(row_y + 3) = 255;
                                row_y += m_n_channels;
                                old_row_y += old_m_n_channels;
                        }
                }
                delete[] old_m_data;
        }

        if (m_n_channels == 3) {
                int old_m_n_channels = m_n_channels;
                uchar* old_m_data = data();
                m_n_channels = 4;
                m_data = new uchar[m_step * m_height * m_n_channels];
                for (int y = 0; y < m_height; y++) {
                        uchar* row_y = data(y);
                        uchar* old_row_y = old_m_data + y * m_step * old_m_n_channels;
                        for (int x = 0; x < m_width; x++) {
                                *row_y = *old_row_y;
                                *(row_y + 1) = *(old_row_y + 1);
                                *(row_y + 2) = *(old_row_y + 2);
                                *(row_y + 3) = 255;
                                row_y += m_n_channels;
                                old_row_y += old_m_n_channels;
                        }
                }
                delete[] old_m_data;
        }
}

void Image::write_pnm(const std::string& filename) const
{       
        string magic_head;
        ofstream fout;
        string extended_name;

        if (m_n_channels == 1) {
                magic_head = "P5";
                extended_name = filename + ".pgm";
        }
        else {
                magic_head = "P6";
                extended_name = filename + ".ppm";
        }
        fout.open(extended_name.c_str(), ios::out | ios::binary);
        fout << magic_head << endl;
        fout << m_width << " " << m_height << endl;
        fout << "255" << endl;
        if (m_n_channels == 4) {
                for (int y = 0; y < m_height; y++) {
                        const uchar* row_data = this->data(y);
                        for (int x = 0; x < m_width; x++) {
                                fout << *row_data;
                                fout << *(row_data + 1);
                                fout << *(row_data + 2);
                                row_data += m_n_channels;
                        }
                }
        }
        else {
                for (int y = 0; y < m_height; y++) {
                        const uchar* row_data = this->data(y);
                        int number_of_item_in_row = m_width * m_n_channels;
                        for (int x = 0; x < number_of_item_in_row; x++) {
                                fout << *row_data;
                                row_data++;
                        }
                }
        }
        fout.close();
}

void Image::load_pnm(const std::string& filename)       
{
        ifstream fin(filename);
        
        if(!fin){ cerr << "Error opening file!" << endl; exit(1); }
        
        string magic_head;
        fin >> magic_head;

        int file_n_channels;
        if (magic_head == "P5") { file_n_channels = 1; }
        else if (magic_head == "P6") {file_n_channels = 3; }
        else{ cerr << "Not Valid Type of Image!" << endl; exit(1); }

        fin >> m_width;
        fin >> m_height;

        int max_value;
        fin >> max_value;

        m_step = m_width;
        m_n_channels = 4;

        if (m_data != nullptr) delete[] m_data;

        m_data = new uchar[m_step * m_height * m_n_channels];
        
        if (file_n_channels == 1) {
                uchar value;
                for (int y = 0; y < m_height; y++) {
                        uchar* row_y = data(y);
                        for (int x = 0; x < m_width; x++){
                                fin >> value;
                                *row_y = value;
                                *(row_y + 1) = value;
                                *(row_y + 2) = value;
                                *(row_y + 3) = 255;
                                row_y += m_n_channels;
                        }
                }
        }

        if (file_n_channels == 3) {
                uchar value;
                for (int y = 0; y < m_height; y++) {
                        uchar* row_y = data(y);
                        for (int x = 0; x < m_width; x++) {
                                fin >> value;
                                *row_y = value;
                                fin >> value;
                                *(row_y + 1) = value;
                                fin >> value;
                                *(row_y + 2) = value;
                                *(row_y + 3) = 255;
                                row_y += m_n_channels;
                        }
                }
        }
        fin.close();
}
}
