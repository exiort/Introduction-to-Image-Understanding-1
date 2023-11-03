#include <string>

namespace ceng391 {
typedef unsigned char uchar;

class Image
{
public:
        Image(int width, int height, int step = -1, int channels = 1);
        ~Image();

        int w() const { return m_width; }
        int h() const { return m_height; }
        int step() const { return m_step; }

        const uchar *data() const { return m_data; }
        uchar *      data()       { return m_data; }
        const uchar *data(int y) const { return m_data + y*m_step*m_n_channels; }
        uchar *      data(int y)       { return m_data + y*m_step*m_n_channels; }

        void set_grayscale(uchar value) { set_rect_grayscale(0, 0, m_width, m_height, value); };
        void set_rect_grayscale(int x_tl, int y_tl, int width, int height, uchar value);

        void set_rgb(uchar* values) { set_rect_rgb(0, 0, m_width, m_height, values); };
        void set_rect_rgb(int x_tl, int y_tl, int width, int height, uchar* values);

        void set_rgba(uchar* values) { set_rect_rgba(0, 0, m_width, m_height, values); };
        void set_rect_rgba(int x_tl, int y_tl, int witdth, int height, uchar* values);

        void to_grayscale();
        void to_rgb();
        void to_rgba();

        void write_pnm(const std::string& filename) const;
        void load_pnm(const std::string& filename);

private:
        int m_width;
        int m_height;
        int m_step;
        int m_n_channels;

        uchar *m_data;
};

}
