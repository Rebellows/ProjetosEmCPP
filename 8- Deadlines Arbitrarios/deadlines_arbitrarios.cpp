#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

#define MAX_TASKS 10

using namespace std;

struct Task {
    int j, c, p, d;
    Task(int p_j=0, int p_c=0, int p_p=0, int p_d=0) {
        j = p_j;
        c = p_c;
        p = p_p;
        d = p_d;
    }
    string str() {
        stringstream ss;
        ss << j << " " << c << " " << p << " " << d;
        return ss.str();
    }
};

int main() {
    Task tasks[MAX_TASKS];
    int numTasks;
    vector<vector<string>> output; // vetor pra mandar todas as saidas junto

    while (true) {
        // INPUT
        cin >> numTasks;
        if (numTasks == 0) break;

        for (int i = 0; i < numTasks; i++)
            cin >> tasks[i].j >> tasks[i].c >> tasks[i].p >> tasks[i].d;

		vector<string> group; // adiciona cada execucao no vetor de saida
        for (int i = 0; i < numTasks; i++) {
            if (tasks[i].d > tasks[i].p) {
                int r = -1;
                bool sched = false;

                // PROCESSING
                int q = 0, Wi = (q+1) * tasks[i].c; // estados iniciais
                while (1) {
                    int Wi_aux = -1;

                    while (Wi != Wi_aux) { // iterando ate establizar o Wi
                        Wi_aux = Wi;
                        int sum = 0;
                        for (int j = 0; j < i; j++) { // loop do somatorio
                            int aux = ceil((Wi + tasks[j].j) / (double)tasks[j].p);
                            sum += aux * tasks[j].c;
                        }

                        Wi = (q+1) * tasks[i].c + sum;
                    }

                    int Ri = tasks[i].j + Wi - (q * tasks[i].p); // regra do tempo de resposta
                    if (Ri > r) r = Ri;

                    if (Wi <= ((q+1) * tasks[i].p)) { // criterio de parada
                        sched = (r <= tasks[i].d);
                        break;
                    }

                    q++;
                }

                // cria a saida
                stringstream ss;
                ss << (i+1) << " " << r << " " << (sched ? "YES" : "NO");
                group.push_back(ss.str());
            }
        }
		output.push_back(group);
    }

    // OUTPUT
	for (int i = 0; i < output.size(); i++) {
		for (auto &line : output[i]) 
			cout << line << endl;
		cout << endl;
	}

    return 0;
}