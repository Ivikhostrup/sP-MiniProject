#ifndef PLOT_HPP
#define PLOT_HPP

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

class Plot
{
    std::string title;
    struct app_t;
    struct chart_t;
    std::unique_ptr<app_t> app;      // pimpl of the application
    std::unique_ptr<chart_t> chart;  // pimpl of the chart
    std::string x_axis_label;
    std::string y_axis_label;

public:
    Plot(std::string title, std::string x_axis_label, std::string y_axis_label, int width, int height);
    Plot(const Plot&) = delete;
    Plot& operator=(const Plot&) = delete;
    Plot(Plot&&) noexcept = default;
    Plot& operator=(Plot&&) = default;
    ~Plot() noexcept;
    void save_to_png(const std::string &filename);
    void scatter(const std::string& name, const std::vector<double>& x, const std::vector<double>& y);
    void lines(const std::string& name, const std::vector<double>& x, const std::vector<double>& y);
    void plot_data(const std::vector<double>& time, const std::unordered_map<std::string, std::vector<double>>& species_quantities);

    void process();
};

#endif //PLOT_HPP
