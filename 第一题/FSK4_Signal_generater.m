function FSK4_Signal = FSK4_Signal_generater(symbol_rate, bits_per_symbol, snr_dB, signal_percentage)
    num_symbols = floor(256 * signal_percentage);

    % Generate random symbol indices (0, 1, 2, 3)
    data = randi([0, 3], 1, num_symbols * bits_per_symbol);

    % Define frequencies for 4FSK modulation
    frequencies = [100e3, 200e3, 300e3, 400e3]; % Adjust frequencies as needed

    % Generate FSK4 modulated signal
    t_signal = 0:1/symbol_rate:(num_symbols * bits_per_symbol / symbol_rate - 1/symbol_rate);
    fsk4_signal = cos(2 * pi * frequencies(data + 1) .* t_signal);
    
    % �������ź�Ƭ�Σ�Ϊ0����
    signal_front = floor(rand * (256 - num_symbols));
    signal_back = 256 - num_symbols - signal_front;
    fsk4_signal_combine = [zeros(1,signal_front),fsk4_signal,zeros(1,signal_back)];
    
    % �ϲ����ڲ壬���������˲�����������Ϊ4�������źŲ����ʣ���ʵ�ֳ���1024���ź�
    upsampled_signal = upsample(fsk4_signal_combine,4);

    %%% ƽ���������˲��� %%%
    rolloff = 0.35; % ����ϵ��
    span = 10; % �˲����ķ���������
    sps = 4; % ÿ�����ŵ�������
    rcosine_filter = rcosdesign(rolloff, span, sps);
    % ���ϲ�������źŽ����˲���ȥ��������ֵ����ĸ�Ƶ����
    filtered_signal = filter(rcosine_filter, 1, upsampled_signal);
    % Add noise
    noise_power = 10^(-snr_dB/10);
    noise = sqrt(noise_power/2) * (randn(1, length(filtered_signal)) + 1i * randn(1, length(filtered_signal)));
    received_signal = filtered_signal + noise;

    FSK4_Signal = received_signal;
    t = 0:1/symbol_rate:(length(filtered_signal)/symbol_rate - 1/symbol_rate);

    % Uncomment the following lines if you want to display the signals
    figure;
    subplot(3, 1, 1);
    plot(t_signal, fsk4_signal);
    title('4FSK Modulated Signal');

    subplot(3, 1, 2);
    plot(t, received_signal);
    title('Received Signal');

    subplot(3, 1, 3);
    plot(t, real(received_signal), 'r');
    hold on;
    plot(t, imag(received_signal), 'b');
    title('Received Signal (Real and Imaginary)');
    legend('Real', 'Imaginary');
end
