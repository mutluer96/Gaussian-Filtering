#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<string>
#include<cmath>
#include<time.h>

//Mucahid Mutluer ID:152120191072
//Edge Mirror iþleminin niteliði duzeltildi 

using namespace std;
void yazdir(double** &dizi, int* k, int* l)
{
	for (int i = 0; i < *k; i++)
	{
		for (int j = 0; j < *l; j++)
		{
			cout << setw(10) << dizi[i][j];
		}
		cout << endl;
	}
}

ofstream outfile;

void dosyaya_yazdir(double** &dizi, int* k, int* l)
{
	for (int i = 0; i < *k; i++)
	{
		for (int j = 0; j < *l; j++)
		{
			outfile << setw(10) << left << showpoint << setprecision(4) << dizi[i][j] << " ";
		}
		outfile << endl;
	}
}

void dosyaya_son_yazdir(double** &dizi, int* k, int* l)
{
	for (int i = 0; i < *k; i++)
	{
		outfile << "			";
		for (int j = 0; j < *l; j++)
		{
			outfile << setw(10) << left << showpoint << setprecision(4) << dizi[i][j] << " ";
		}
		outfile << endl;
	}
}

double fRand(int, int);

int main()
{
	int im_size, fsize;
	int black, white;
	int grid_n;
	srand(time(NULL));
	ifstream infile;
	string dosyaAdi = "inputs.txt";
	outfile.open("A_Gaussian.txt");
	infile.open("inputs.txt");

	if (!infile)
	{
		cout << "Can not open the input file.!" << endl;
		cout << "Program Terminates!!!" << endl;
		return 1;
	}
	outfile << fixed << showpoint;
	outfile << setw(9) << setprecision(5);
	cout << "Processing Data..." << endl;
	cout << "Mucahid Mutluer Student ID: 152120191072" << endl;

	infile >> im_size >> fsize >> black >> white;

	if ((im_size > 9) || (fsize > 9))
	{
		cout << endl << "Image size and filter size should be less than 10, Program Terminates!" << endl;
		exit(0);
	}


	grid_n = 21;

	double** filter = new double*[fsize];
	for (int i = 0; i < fsize; i++)
	{
		filter[i] = new double[fsize];
	} // filtre matrisin 2d arrayini kurdum

	for (int i = 0; i < fsize; i++)
	{
		for (int j = 0; j < fsize; j++)
		{
			filter[i][j] = 0.0;
		}
	}
	int i, j, d, f;
	double value;
	f = fsize / 2;

	cout.setf(ios::fixed);
	cout.precision(4);

	for (d = 0; d < f; d++)
	{
		value = 1.0 / pow((2 * (d + 1) + 1), 2);
		for (i = -(d + 1); i <= d + 1; i++)
		{
			for (j = -(d + 1); j <= d + 1; j++)
				filter[f - i][f - j] = filter[f - i][f - j] + value;
		}

	}


	for (i = 0; i < fsize; i++)
	{
		for (j = 0; j < fsize; j++)
		{
			filter[i][j] = filter[i][j] / static_cast<double>(fsize);
		}
	}

	double** matris = new double*[grid_n];
	for (int i = 0; i < grid_n; i++)
	{
		matris[i] = new double[grid_n];
	}

	int sinir = ((grid_n - im_size) / 2);

	int Y = grid_n - sinir;

	if ((grid_n % 2) == (im_size % 2))
	{
		sinir--;
	}

	for (i = 0; i < grid_n; i++)
	{
		for (j = 0; j < grid_n; j++)
		{

			if ((i > sinir) && (i < Y))
			{
				if ((j > sinir) && (j < Y))
				{
					matris[i][j] = fRand(white, black);
				}
				else
				{
					matris[i][j] = 0;
				}
			}
			else
			{
				matris[i][j] = 0;
			}
		}
	}//simdi sirada im_size x im_size lik resmi bastirmak var

	double** resim = new double*[im_size];
	for (int i = 0; i < im_size; i++)
	{
		resim[i] = new double[im_size];
	}//im_size x im_size 2d arrayini kurdum

	for (i = 0; i < grid_n; i++)
	{
		for (j = 0; j < grid_n; j++)
		{
			if ((i > sinir) && (i < Y))
			{
				if ((j > sinir) && (j < Y))
				{
					resim[i - (sinir + 1)][j - (sinir + 1)] = matris[i][j];
				}
			}
		}
	}

	double** aynali = new double*[grid_n];
	for (int i = 0; i < grid_n; i++)
	{
		aynali[i] = new double[grid_n];
	} // aynali matrisin 2d arrayini kurdum

	for (i = 0; i < grid_n; i++)
	{
		for (j = 0; j < grid_n; j++)
		{
			aynali[i][j] = matris[i][j]; //matristen aynaliya kopyalama yaptým
		}//sýrada aynalamayý yapmak var
	}
	int mir;
	mir = fsize / 2;

	for (i = 1; i <= mir; i++)//kosedeki kare aynalama
	{
		for (j = 1; j <= mir; j++)
		{
			aynali[sinir + 1 - i][sinir + 1 - j] = matris[sinir + 1][sinir + 1];
		}
	}

	for (i = 1; i <= mir; i++)//kosedeki kare aynalama
	{
		for (j = 1; j <= mir; j++)
		{
			aynali[sinir + 1 - i][Y - 1 + j] = matris[sinir + 1][Y - 1];
		}
	}

	for (i = 1; i <= mir; i++)//kosedeki kare aynalama
	{
		for (j = 1; j <= mir; j++)
		{
			aynali[Y - 1 + i][sinir + 1 - j] = matris[Y - 1][sinir + 1];
		}
	}

	for (i = 1; i <= mir; i++)//kosedeki kare aynalama
	{
		for (j = 1; j <= mir; j++)
		{
			aynali[Y - 1 + i][Y - 1 + j] = matris[Y - 1][Y - 1];
		}
	}

	for (i = 1; i <= mir; i++)//ust kenar
	{
		for (j = 1; j <= (Y - sinir - 1); j++)
		{
			aynali[sinir - i + 1][sinir + j] = matris[sinir + 1][sinir + j];
		}
	}

	for (i = 1; i <= mir; i++)//alt kenar
	{
		for (j = 1; j <= (Y - sinir - 1); j++)
		{
			aynali[Y + i - 1][sinir + j] = matris[Y - 1][sinir + j];
		}
	}

	for (i = 1; i <= (Y - sinir - 1); i++)//sol kenar
	{
		for (j = 1; j <= (mir); j++)
		{
			aynali[sinir + i][sinir + 1 - j] = matris[sinir + i][sinir + 1];
		}
	}

	for (i = 1; i <= (Y - sinir - 1); i++)//sag kenar
	{
		for (j = 1; j <= (mir); j++)
		{
			aynali[sinir + i][Y - 1 + j] = matris[sinir + i][Y - 1];
		}
	}

	double** outmatrix = new double*[grid_n];
	for (int i = 0; i < grid_n; i++)
	{
		outmatrix[i] = new double[grid_n];
	}//output gridimizi kuralým

	int m, n;//bu degiskenlerle 3. ve 4. ic donguleri donecegim
	double sum = 0.0;

	for (i = 0; i < grid_n; i++)
	{
		for (j = 0; j < grid_n; j++)
		{
			outmatrix[i][j] = 0.0;
		}
	}//outmatrixi kenarlarda null degerler cikmasin diye 0 ile initialize ettim

	if (fsize % 2 == 1)
	{
		for (i = (sinir + 1); i < Y; i++)//bu dortlu dongude output gridi hesaplar
		{
			for (j = (sinir + 1); j < Y; j++)
			{
				for (m = -mir; m < mir + 1; m++)
				{
					for (n = -mir; n < mir + 1; n++)
					{
						sum = sum + ((filter[mir + m][mir + n] * aynali[i + m][j + n]) / static_cast<double>(fsize*fsize));
					}
				}
				outmatrix[i][j] = sum;
				sum = 0;
			}
		}
	}
	else
	{
		for (i = (sinir + 1); i < Y; i++)//bu dortlu dongude output gridi hesaplar
		{
			for (j = (sinir + 1); j < Y; j++)
			{
				for (m = -mir; m < mir; m++)
				{
					for (n = -mir; n < mir; n++)
					{
						sum = sum + ((filter[mir + m][mir + n] * aynali[i + m][j + n]) / static_cast<double>(fsize*fsize));
					}
				}
				outmatrix[i][j] = sum;
				sum = 0;
			}
		}
	}

	double** outresim = new double*[im_size];
	for (int i = 0; i < im_size; i++)
	{
		outresim[i] = new double[im_size];
	}//im_size x im_size output resim 2d arrayini kurdum

	for (i = 0; i < grid_n; i++)
	{
		for (j = 0; j < grid_n; j++)
		{
			if ((i > sinir) && (i < Y))
			{
				if ((j > sinir) && (j < Y))
				{
					outresim[i - (sinir + 1)][j - (sinir + 1)] = outmatrix[i][j];
				}
			}
		}
	}

	outfile << "Input Image " << "(" << im_size << "x" << im_size << ")" << endl;
	outfile << setfill('-') << setw(26 + (im_size * 10)) << right;
	outfile << "-" << endl;
	outfile << setfill(' ');
	dosyaya_son_yazdir(resim, &im_size, &im_size);
	outfile << setfill('-') << setw(26 + (im_size * 10)) << right;
	outfile << "-" << endl;
	outfile << setfill(' ');

	outfile << "Gaussian Filter " << "(" << fsize << "x" << fsize << ")" << endl;
	outfile << setfill('-') << setw(24 + (fsize * 10)) << right;
	outfile << "-" << endl;
	outfile << setfill(' ');
	dosyaya_son_yazdir(filter, &fsize, &fsize);
	outfile << setfill('-') << setw(24 + (fsize * 10)) << right;
	outfile << "-" << endl;
	outfile << setfill(' ');

	outfile << "Input Grid: Edge Mirrored Image" << "(" << grid_n << "x" << grid_n << ")" << endl;
	outfile << setfill('-') << setw(226) << right;
	outfile << "-" << endl;
	outfile << setfill(' ');
	dosyaya_yazdir(aynali, &grid_n, &grid_n);
	outfile << setfill('-') << setw(226) << right;
	outfile << "-" << endl;
	outfile << setfill(' ');

	outfile << "Output Grid: Cutted-Edge Image " << "(" << grid_n << "x" << grid_n << ")" << endl;
	outfile << setfill('-') << setw(226) << right;
	outfile << "-" << endl;
	outfile << setfill(' ');
	dosyaya_yazdir(outmatrix, &grid_n, &grid_n);
	outfile << setfill('-') << setw(226) << right;
	outfile << "-" << endl;
	outfile << setfill(' ');

	outfile << "Output (Filtered) Image " << "(" << im_size << "x" << im_size << ")" << endl;
	outfile << setfill('-') << setw(24 + (im_size * 10)) << right;
	outfile << "-" << endl;
	outfile << setfill(' ');
	dosyaya_son_yazdir(outresim, &im_size, &im_size);
	outfile << setfill('-') << setw(24 + (im_size * 10)) << right;
	outfile << "-" << endl;
	outfile << setfill(' '); 


	cout << "Input Image " << "(" << im_size << "x" << im_size << ")" << endl;
	cout << setfill('-') << setw(26 + (im_size * 10)) << right;
	cout << "-" << endl;
	cout << setfill(' ');
	yazdir(resim, &im_size, &im_size);
	cout << setfill('-') << setw(26 + (im_size * 10)) << right;
	cout << "-" << endl;
	cout << setfill(' ');

	cout << "Gaussian Filter " << "(" << fsize << "x" << fsize << ")" << endl;
	cout << setfill('-') << setw(24 + (fsize * 10)) << right;
	cout << "-" << endl;
	cout << setfill(' ');
	yazdir(filter, &fsize, &fsize);
	cout << setfill('-') << setw(24 + (fsize * 10)) << right;
	cout << "-" << endl;
	cout << setfill(' ');

	cout << "Input Grid: Edge Mirrored Image" << "(" << grid_n << "x" << grid_n << ")" << endl;
	cout << setfill('-') << setw(226) << right;
	cout << "-" << endl;
	cout << setfill(' ');
	yazdir(aynali, &grid_n, &grid_n);
	cout << setfill('-') << setw(226) << right;
	cout << "-" << endl;
	cout << setfill(' ');

	cout << "Output Grid: Cutted-Edge Image " << "(" << grid_n << "x" << grid_n << ")" << endl;
	cout << setfill('-') << setw(226) << right;
	cout << "-" << endl;
	cout << setfill(' ');
	yazdir(outmatrix, &grid_n, &grid_n);
	cout << setfill('-') << setw(226) << right;
	cout << "-" << endl;
	cout << setfill(' ');

	cout << "Output (Filtered) Image " << "(" << im_size << "x" << im_size << ")" << endl;
	cout << setfill('-') << setw(24 + (im_size * 10)) << right;
	cout << "-" << endl;
	cout << setfill(' ');
	yazdir(outresim, &im_size, &im_size);
	cout << setfill('-') << setw(24 + (im_size * 10)) << right;
	cout << "-" << endl;
	cout << setfill(' ');


	for (int i = 0; i < grid_n; i++)
	{
		delete[] matris[i];
	}
	delete[] matris;
	matris = NULL;

	for (int i = 0; i < grid_n; i++)
	{
		delete[] aynali[i];
	}
	delete[] aynali;
	aynali = NULL;

	for (int i = 0; i < im_size; i++)
	{
		delete[] resim[i];
	}
	delete[] resim;
	resim = NULL;

	for (int i = 0; i < fsize; i++)
	{
		delete[] filter[i];
	}
	delete[] filter;
	filter = NULL;

	for (int i = 0; i < grid_n; i++)
	{
		delete[] outmatrix[i];
	}
	delete[] outmatrix;
	outmatrix = NULL;

	for (int i = 0; i < im_size; i++)
	{
		delete[] outresim[i];
	}
	delete[] outresim;
	outresim = NULL;
	infile.close();
	outfile.close();
	system("pause");
	return 1;
}

double fRand(int fMin, int fMax)
{
	double f = (double)((rand() % (fMax - fMin)) + fMin);
	return f;
}
