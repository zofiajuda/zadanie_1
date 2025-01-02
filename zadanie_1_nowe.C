using namespace std;

void name_histo(int num_his, TH1F *h)
{
    char *his = new char[100];
    sprintf(his, "%s%d", "sygnal nr ", num_his);
    h->SetTitle(his);
    h->GetXaxis()->SetTitle("czas [ns] ");
    h->GetYaxis()->SetTitle("amplituda [V] ");

    h->SetLineColor(kBlack);
    gStyle->SetOptStat(000);

    return;
}
double shift_baseline(TH1F *h, int nbins)
{
    double baseline;
    int liczba_sr = 50;
    for (int i = 0; i < liczba_sr; i++)
    {
        baseline += h->GetBinContent(i);
    }
    baseline = baseline / liczba_sr;
    for (int j = 0; j < nbins; j++)
    {
        h->SetBinContent(j, h->GetBinContent(j) - baseline);
    }
    h->GetYaxis()->SetTitle("amplituda [mV] ");
    h->SetLineColor(kRed);
    return baseline;
}

void zadanie_1_nowe(TString filename = "wave_0.dat")
{
    int nbins = 1024;
    // ##################################
    // Inicjalizacja histo
    TCanvas *canvas = new TCanvas("canvas", "clickme", 0, 0, 1028, 700);
    TH1F *h = new TH1F("sygnal", "sygnal", nbins - 1, 0, 1023);
    // int i = 50;

    // ##################################
    // Dodatkowe funkcje
    //*****************
    // Wyjscie z  programu
    cout << "Co ile histogramow zapytac Cie czy chcesz wyjsc z programu?" << endl;
    int wyjsc;
    cin >> wyjsc;
    int k = 0; // iterator do wyjsc
    //*****************
    // baseline
    cout << "Czy odjąć linię bazową [y/n]?" << endl;
    string srodkuj;
    cin >> srodkuj;

    // ###################################
    // Główna funkcja
    bool EndFile = false;
    int i = 0;
    fstream myfile;
    myfile.open(filename, ios::binary | ios::in);

    if (!myfile.is_open())
    {
        cout << "Unable to open file" << endl;
    }
    else
    {
        // ###############################
        // PĘTLA PO WSZYSTKICH HISTOGRAMACH
        do
        {
            if (!myfile.eof())
            {
                name_histo(i, h);
                // ##################################
                // PĘTLA WYPEŁNIAJĄCA JEDEN HISTOGRAM
                for (int j = 0; j < nbins; j++)
                {
                    //********************************
                    // CZYTAJ BINARKĘ i WYPEŁNIJ HISTO
                    float x;
                    myfile.read((char *)&x, sizeof(float));
                    h->SetBinContent(j, x / 4.096);
                    //********************************
                    // FINALIZOWANIE WYPEŁNIONEGO HISTOGRAMU
                    if (j == nbins - 1)
                    {
                        canvas->cd();
                        h->Draw();
                        // PRZESUNIECIE BASELINE
                        if (srodkuj == "y")
                        {
                            double baseline = shift_baseline(h, nbins);
                            char *base = new char[100];
                            sprintf(base, "%s%f%s", "baseline zostal przesuniety o  ", baseline, " [mV]");
                            TPaveText *pt = new TPaveText(.66, .87, .94, .97, "NDC");
                            pt->AddText(base);
                            pt->Draw();
                        }

                        canvas->Update();
                        canvas->WaitPrimitive();
                    }
                }
            }
            else
            {
                EndFile = true;
            }
            //*********************************************************
            // FUNKCJA POZWALAJĄCA WYJŚĆ Z PĘTLI
            if (i == wyjsc * (k + 1))
            {
                cout << "Czy chcesz wyjsc z programu? [y/n]" << endl;
                string odp;
                cin >> odp;
                if (odp == "y")
                {
                    break;
                }
                k++;
            }
            i++;
        } while (!EndFile);
    }
}