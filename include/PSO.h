//
// Created by iceytan on 18-12-9.
//

#ifndef PSO_H
#define PSO_H

#include <iostream>
#include <random>
#include <vector>
#include <functional>

using namespace std;


namespace {
    class PSO {
        struct Particle {
            double min_loss;
            vector<double> velocity;
            vector<double> position;
            vector<double> pbest;

            Particle() :
                    min_loss(std::numeric_limits<double>::max()) {}
        };

        vector<Particle> mParticles;

        std::function<double(vector<double>)> mLossFunction;

        size_t mVariableNum = 1;

        mt19937 mt = mt19937(default_random_engine()());

        double r() {
            return (mt() % 100000) / 100000.0;
        }

    public:

        double w, c1, c2;

        explicit PSO(size_t num_of_variable = 1, double w = 0.5, double c1 = 2, double c2 = 10);

        void SetLossFunction(const std::function<double(vector<double>)> &loss_func);

        vector<double> Process(int max_iterate_time, double min_loss, size_t num_of_particles = 20,
                               vector<double> initial_values = vector<double>(1));

    };


    PSO::PSO(size_t num_of_variable, double w, double c1, double c2) {
        this->w = w;
        this->c1 = c1;
        this->c2 = c2;
        mVariableNum = num_of_variable;
    }

    void PSO::SetLossFunction(const std::function<double(vector<double>)> &loss_func) {
        mLossFunction = loss_func;
    }

    vector<double>
    PSO::Process(int max_iterate_time, double min_loss, size_t num_of_particles, vector<double> initial_values) {

        mParticles.clear();
        for (int i = 0; i < num_of_particles; ++i) {
            Particle particle;
            vector<double>( mVariableNum ).swap(particle.velocity);
            vector<double>( mVariableNum ).swap(particle.position);
            vector<double>( mVariableNum ).swap(particle.pbest);
            // 在初始位置附近散布
            for (int d = 0; d < mVariableNum; ++d) {
                particle.pbest[d] = particle.position[d] =
                        initial_values[d] + r() * num_of_particles * 2 - num_of_particles;
            }
            mParticles.emplace_back(particle);
        }

        double gloss = std::numeric_limits<double>::max();
        vector<double> gbest(initial_values);

        for (int i = 0; i < max_iterate_time; ++i) {
            if (gloss < min_loss) {
                cout << "Arrival min loss point: loss = " << gloss << ", iteration = " << i + 1 << endl;
                break;
            }

            for (auto &p: mParticles) {
                double _loss = mLossFunction(p.position);

                if (_loss < p.min_loss) {
                    p.min_loss = _loss;
                    p.pbest = p.position;
                }
                if (_loss < gloss) {
                    gloss = _loss;
                    gbest = p.position;
                }
            }

            if (i == max_iterate_time - 1) break;

            for (auto &p: mParticles) {
                for (int d = 0; d < mVariableNum; ++d) {
                    p.velocity[d] = w * p.velocity[d] + c1 * r() * (p.pbest[d] - p.position[d]) +
                                    c2 * r() * (gbest[d] - p.position[d]);
                    p.position[d] = p.position[d] + p.velocity[d];
                }
            }
        }
        cout << "final loss = " << gloss << endl;
        return gbest;
    }
}


#endif //PSO_H
