/**
 * @file rmsproboptimizer.cpp
 * @auther yefajie
 * @data 2018/6/25
 **/
#include "rmsproboptimizer.h"

RMSProbOptimizer::RMSProbOptimizer(float learning_rate, const vector<int>& decay_steps, float decay_rate):
    Optimizer(learning_rate, decay_steps), decay_rate_(decay_rate) {
}

void RMSProbOptimizer::optimize(shared_ptr<Chunk>& param, const string& param_name, int iter) {
    int decay_index = find_if(decay_steps_.begin(), decay_steps_.end(),
                              [&iter](int step) {return step > iter;}) - decay_steps_.begin();
    float learning_rate = learning_rate_ * pow(0.1, decay_index);

    if (accumulate_squared_gradient_.find(param_name) == accumulate_squared_gradient_.end()) {
        accumulate_squared_gradient_[param_name] = Chunk(param->shape());
    }
    const float* diff = param->const_diff();
    float* data = param->data();
    float* acc_squared_grad = accumulate_squared_gradient_[param_name].data();
    for (int i = 0; i < param->count(); ++i) {
        acc_squared_grad[i]  = decay_rate_ * acc_squared_grad[i] + (1 - decay_rate_) * diff[i] * diff[i];
        float update = -(learning_rate / sqrt(acc_squared_grad[i] + 1e-7F)) * diff[i];
        data[i] += update;
    }
}
