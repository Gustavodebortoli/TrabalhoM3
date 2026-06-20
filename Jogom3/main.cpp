#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    // ----- Limites do sistema (definidos como constantes) -----
    const int MAX_VEICULOS = 20;
    const int MAX_SERVICOS = 10;      // qtd maxima de servicos por veiculo
    const int KM_INTERVALO_REVISAO = 10000; // intervalo recomendado p/ revisao

    // ----- Vetores: um veiculo por posicao -----
    string placa[MAX_VEICULOS];
    string proprietario[MAX_VEICULOS];
    string modelo[MAX_VEICULOS];
    int kmAtual[MAX_VEICULOS];
    int qtdServicos[MAX_VEICULOS]; // quantos servicos cada veiculo ja tem
    int totalVeiculos = 0;

    // ----- Matrizes: linha = veiculo, coluna = servico daquele veiculo -----
    string tipoServico[MAX_VEICULOS][MAX_SERVICOS];
    float custoServico[MAX_VEICULOS][MAX_SERVICOS];
    int kmServico[MAX_VEICULOS][MAX_SERVICOS];

    for (int i = 0; i < MAX_VEICULOS; i++) {
        qtdServicos[i] = 0;
    }

    int opcao;

    do {
        cout << "\n===== SISTEMA DE HISTORICO DE MANUTENCAO VEICULAR =====\n";
        cout << "1 - Cadastrar veiculo\n";
        cout << "2 - Registrar servico de manutencao\n";
        cout << "3 - Consultar historico de um veiculo\n";
        cout << "4 - Relatorio: gasto total por veiculo (e maior gasto)\n";
        cout << "5 - Verificar alerta de revisao preventiva\n";
        cout << "6 - Listar todos os veiculos cadastrados\n";
        cout << "0 - Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        // ===================== 1) CADASTRAR VEICULO =====================
        if (opcao == 1) {
            if (totalVeiculos >= MAX_VEICULOS) {
                cout << "Limite de veiculos cadastrados atingido.\n";
            } else {
                int i = totalVeiculos;
                cout << "\n--- Cadastro de veiculo ---\n";
                cout << "Placa: ";
                cin >> placa[i];
                cout << "Proprietario: ";
                cin.ignore();
                getline(cin, proprietario[i]);
                cout << "Modelo: ";
                getline(cin, modelo[i]);
                cout << "Km atual: ";
                cin >> kmAtual[i];

                qtdServicos[i] = 0;
                totalVeiculos++;
                cout << "Veiculo cadastrado com sucesso!\n";
            }
        }

        // ================ 2) REGISTRAR SERVICO DE MANUTENCAO ================
        else if (opcao == 2) {
            if (totalVeiculos == 0) {
                cout << "Nenhum veiculo cadastrado ainda.\n";
            } else {
                cout << "\n--- Registrar servico ---\n";
                for (int i = 0; i < totalVeiculos; i++) {
                    cout << i << " - " << placa[i] << " (" << modelo[i] << ")\n";
                }
                int idx;
                cout << "Escolha o numero do veiculo: ";
                cin >> idx;

                if (idx < 0 || idx >= totalVeiculos) {
                    cout << "Veiculo invalido.\n";
                } else if (qtdServicos[idx] >= MAX_SERVICOS) {
                    cout << "Limite de servicos para este veiculo atingido.\n";
                } else {
                    int s = qtdServicos[idx]; // proxima posicao livre na matriz
                    cout << "Tipo de servico (ex: troca de oleo, freio, correia): ";
                    cin.ignore();
                    getline(cin, tipoServico[idx][s]);
                    cout << "Custo (R$): ";
                    cin >> custoServico[idx][s];
                    cout << "Km no momento do servico: ";
                    cin >> kmServico[idx][s];

                    if (kmServico[idx][s] > kmAtual[idx]) {
                        kmAtual[idx] = kmServico[idx][s]; // atualiza km do veiculo
                    }

                    qtdServicos[idx]++;
                    cout << "Servico registrado com sucesso!\n";
                }
            }
        }

        // ================ 3) CONSULTAR HISTORICO DE UM VEICULO ================
        else if (opcao == 3) {
            if (totalVeiculos == 0) {
                cout << "Nenhum veiculo cadastrado ainda.\n";
            } else {
                for (int i = 0; i < totalVeiculos; i++) {
                    cout << i << " - " << placa[i] << " (" << modelo[i] << ")\n";
                }
                int idx;
                cout << "Escolha o numero do veiculo: ";
                cin >> idx;

                if (idx < 0 || idx >= totalVeiculos) {
                    cout << "Veiculo invalido.\n";
                } else {
                    cout << "\n--- Historico de " << placa[idx] << " - " << modelo[idx] << " ---\n";
                    cout << "Proprietario: " << proprietario[idx] << "\n";
                    cout << "Km atual: " << kmAtual[idx] << "\n";

                    if (qtdServicos[idx] == 0) {
                        cout << "Nenhum servico registrado para este veiculo.\n";
                    } else {
                        for (int s = 0; s < qtdServicos[idx]; s++) {
                            cout << "  Servico " << (s + 1) << ": "
                                 << tipoServico[idx][s]
                                 << " | Km: " << kmServico[idx][s]
                                 << " | Custo: R$ " << fixed << setprecision(2)
                                 << custoServico[idx][s] << "\n";
                        }
                    }
                }
            }
        }

        // ========== 4) RELATORIO: GASTO TOTAL POR VEICULO E MAIOR GASTO ==========
        else if (opcao == 4) {
            if (totalVeiculos == 0) {
                cout << "Nenhum veiculo cadastrado ainda.\n";
            } else {
                float totalPorVeiculo[MAX_VEICULOS];
                int veiculoMaiorGasto = 0;

                for (int i = 0; i < totalVeiculos; i++) {
                    float soma = 0;
                    for (int s = 0; s < qtdServicos[i]; s++) {
                        soma = soma + custoServico[i][s]; // soma os custos da linha i da matriz
                    }
                    totalPorVeiculo[i] = soma;

                    if (totalPorVeiculo[i] > totalPorVeiculo[veiculoMaiorGasto]) {
                        veiculoMaiorGasto = i;
                    }
                }

                cout << "\n--- Gasto total por veiculo ---\n";
                for (int i = 0; i < totalVeiculos; i++) {
                    cout << placa[i] << " (" << modelo[i] << "): R$ "
                         << fixed << setprecision(2) << totalPorVeiculo[i] << "\n";
                }

                cout << "\nVeiculo com maior gasto em manutencao: "
                     << placa[veiculoMaiorGasto] << " (" << modelo[veiculoMaiorGasto]
                     << ") - R$ " << fixed << setprecision(2)
                     << totalPorVeiculo[veiculoMaiorGasto] << "\n";
            }
        }

        // ============== 5) ALERTA DE REVISAO PREVENTIVA ==============
        else if (opcao == 5) {
            if (totalVeiculos == 0) {
                cout << "Nenhum veiculo cadastrado ainda.\n";
            } else {
                cout << "\n--- Alerta de revisao (intervalo: " << KM_INTERVALO_REVISAO << " km) ---\n";

                for (int i = 0; i < totalVeiculos; i++) {
                    int kmUltimoServico = -1;

                    // procura, na linha i da matriz, o servico mais recente (maior km)
                    for (int s = 0; s < qtdServicos[i]; s++) {
                        if (kmServico[i][s] > kmUltimoServico) {
                            kmUltimoServico = kmServico[i][s];
                        }
                    }

                    if (kmUltimoServico == -1) {
                        cout << placa[i] << ": sem servicos registrados, nao e possivel avaliar.\n";
                    } else {
                        int rodados = kmAtual[i] - kmUltimoServico;
                        if (rodados >= KM_INTERVALO_REVISAO) {
                            cout << placa[i] << " (" << modelo[i] << "): ATENCAO, revisao recomendada! ("
                                 << rodados << " km rodados desde o ultimo servico)\n";
                        } else {
                            cout << placa[i] << " (" << modelo[i] << "): OK, faltam "
                                 << (KM_INTERVALO_REVISAO - rodados) << " km para a proxima revisao.\n";
                        }
                    }
                }
            }
        }

        // ================ 6) LISTAR TODOS OS VEICULOS ================
        else if (opcao == 6) {
            if (totalVeiculos == 0) {
                cout << "Nenhum veiculo cadastrado ainda.\n";
            } else {
                cout << "\n--- Veiculos cadastrados ---\n";
                for (int i = 0; i < totalVeiculos; i++) {
                    cout << i << " - " << placa[i] << " | " << modelo[i]
                         << " | Dono: " << proprietario[i]
                         << " | Km: " << kmAtual[i]
                         << " | Servicos registrados: " << qtdServicos[i] << "\n";
                }
            }
        }

        else if (opcao != 0) {
            cout << "Opcao invalida.\n";
        }

    } while (opcao != 0);

    cout << "\nEncerrando o sistema. Ate logo!\n";
    return 0;
}