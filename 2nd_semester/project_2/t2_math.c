#define pi 3.14159265358979323846

struct complex{
    double real;
    double imaginary;
};

struct coefficient{
    double amplitude;
    int frequency;
    struct complex coef;
};

static struct complex euler(double x){
    struct complex euler;
        euler.real = cos(x);
        euler.imaginary = sin(x);
    return euler;
}

struct complex *fourier_dtransform(unsigned char *x, int N){
    struct complex *c = (struct complex *)calloc((N/2)+1,sizeof(struct complex));
    struct complex e;
    int k, t;
    double w;
    for(k = 0 ; k <= N/2 ; k++){
        for(t = 0 ; t < N ; t++){
            w = ((double)t)/((double)N);
            e = euler(-1*k*2*pi*w);
            c[k].real += x[t]*e.real;
            c[k].imaginary += x[t]*e.imaginary;
        }
        if(k == 0){
            c[k].real *= 1/(double)N;
            c[k].imaginary *= 1/(double)N;
        }
        else{
            c[k].real *= 2/(double)N;
            c[k].imaginary *= 2/(double)N;
        }
    }
    return c;
}

unsigned char *fourier_inversedtransform(struct coefficient *c, int N){
    unsigned char *x = (unsigned char *)malloc(sizeof(unsigned char)*N);
    double real;
    struct complex e;
    int t, k;
    double w;

    for(t = 0 ; t < N ; t++){
        real = 0.0;
        w = ((double)t)/((double)N);
        for(k = 0 ; k <= N/2 ; k++){
            e = euler(k*2*pi*w);
            real += ((c[k].coef.real)*(e.real))-((c[k].coef.imaginary)*(e.imaginary));
        }
        x[t] = (unsigned char)(round(real));
    }
    return x;
}

void merge_sort_amp(struct coefficient *vec, int start, int end){
    if ( start == end ) return;
     
    long int mid = ( start + end ) / 2;
    
     merge_sort_amp(vec, start, mid);
     merge_sort_amp(vec, mid + 1, end);
     
    long int k = 0, i = start, j = mid + 1;
    struct coefficient *tempvec = (struct coefficient *)malloc(sizeof(struct coefficient)*(end - start + 1));
    
    while( i < mid + 1 || j < end + 1 ){
        
        if( i == mid + 1 ) {
            tempvec[k] = vec[j];
            k++;
            j++;
        }
        else{
            
            if( j == end + 1 ) {
                tempvec[k] = vec[i];
                i++;
                k++;
            }
            else{
                
                if( vec[i].amplitude > vec[j].amplitude ) {
                    tempvec[k] = vec[i];
                    i++;
                    k++;
                }
                else{
                    tempvec[k] = vec[j];
                    j++;
                    k++;
                }
            }
        }
    }
    
    for( i = start; i <= end; i++ )
        vec[i] = tempvec[i-start];
        
    free(tempvec);
}

void merge_sort_freq(struct coefficient *vec, int start, int end){
    long int i, j, k, mid;
    struct coefficient *tempvec;

    if(start == end) return;

    // ordenacao recursiva das duas metades
    mid = (start + end ) / 2;
    merge_sort_freq(vec, start, mid);
    merge_sort_freq(vec, mid + 1, end);

    // intercalacao no vetor temporario t
    i = start;
    j = mid + 1;
    k = 0;
    tempvec = (struct coefficient *)malloc(sizeof(struct coefficient) * (end - start + 1));

    while(i < mid + 1 || j  < end + 1) {
        if (i == mid + 1 ) { // i passou do final da primeira metade, pegar v[j]
            tempvec[k] = vec[j];
            j++;
            k++;
        }
        else {
            if (j == end + 1) { // j passou do final da segunda metade, pegar v[i]
                tempvec[k] = vec[i];
                i++;
                k++;
            }
            else {
                if (vec[i].frequency < vec[j].frequency) {
                    tempvec[k] = vec[i];
                    i++;
                    k++;
                }
                else {
                    tempvec[k] = vec[j];
                    j++;
                    k++;
                }
            }
        }

    }
    // copia vetor intercalado para o vetor original
    for(i = start; i <= end; i++) {
        vec[i] = tempvec[i - start];
    }
    free(tempvec);
}

struct coefficient *getallmag( struct complex *c , int N ){
    struct coefficient *allmag = (struct coefficient *)malloc(sizeof(struct coefficient)*((N/2)+1));
    
    int i;
    for(i = 0 ; i <= N/2 ; i++){
        allmag[i].amplitude = sqrt(pow(c[i].real,2)+pow(c[i].imaginary,2));
        allmag[i].frequency = i;
        allmag[i].coef = c[i];
    }
    
    return allmag;
}