using System;
using System.IO.Pipes;
using System.Security.AccessControl;
using Microsoft.Win32.SafeHandles;
using System.Text;
using System.Runtime.InteropServices;
using System.Threading;
using System.IO;

namespace CSNamedPipe
{
    public class DataArrivedEventArgs
    {
        public DataArrivedEventArgs(string s)
        {
            Text = s;
        }
        public string Text { get; private set; }
    }

    public class NamedPipeServer
    {
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern SafeFileHandle CreateNamedPipe(
           String pipeName,
           uint dwOpenMode,
           uint dwPipeMode,
           uint nMaxInstances,
           uint nOutBufferSize,
           uint nInBufferSize,
           uint nDefaultTimeOut,
           uint lpSecurityAttributes);

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern int ConnectNamedPipe(
           uint hNamedPipe,
           uint lpOverlapped);

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern int DisconnectNamedPipe(
           SafeFileHandle hNamedPipe);

        public delegate void DataArrivedEventHandler(object sender, DataArrivedEventArgs e);
        public event DataArrivedEventHandler DataArrived;

        public const uint PIPE_ACCESS_DUPLEX = (0x00000003);
        public const uint FILE_FLAG_OVERLAPPED = (0x40000000);
        public const uint PIPE_READMODE_BYTE = (0x0);
        public const uint PIPE_READMODE_MESSAGE = (0x2);

        public class Client
        {
            public SafeFileHandle handle;
            public FileStream stream;
        }

        public const int BUFFER_SIZE = 4096;
        public Client clientse =null;

        public string pipeName;
        Thread listenThread;
        private Thread readThread;
        SafeFileHandle clientHandle;
        public int ClientType;

        public NamedPipeServer(string PName,int Mode)
        {
            pipeName = PName;
            ClientType = Mode;//0 Reading Pipe, 1 Writing Pipe

        }
       
        public void Start()
        {
            this.listenThread = new Thread(new ThreadStart(ListenForClients));
            this.listenThread.Start();
        }
        private void ListenForClients()
        {
            /*
            PipeSecurity pipeSa = new PipeSecurity();
            pipeSa.SetAccessRule(new PipeAccessRule("Everyone",
                PipeAccessRights.ReadWrite, AccessControlType.Allow));

            NamedPipeServerStream pipeServer = new NamedPipeServerStream(
                pipeName,                    // The unique pipe name.
                PipeDirection.InOut,            // The pipe is bi-directional
                NamedPipeServerStream.MaxAllowedServerInstances,
                PipeTransmissionMode.Message,   // Message type pipe 
                PipeOptions.None,               // No additional parameters
                BUFFER_SIZE,                    // Input buffer size
                BUFFER_SIZE,                    // Output buffer size
                pipeSa,                         // Pipe security attributes
                HandleInheritability.None       // Not inheritable
                );

            pipeServer.WaitForConnection();

            */
            
            NativeOverlapped no = new NativeOverlapped();
            while (true)
            {

                clientHandle = CreateNamedPipe(
                    this.pipeName,
                    PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
                    PIPE_READMODE_BYTE,
                    255,
                    BUFFER_SIZE,
                    BUFFER_SIZE,
                    50,
                    0);

                //could not create named pipe
                if (!clientHandle.IsInvalid)
                {

                    int success;
                    //if (ClientType == 0)
                    success = ConnectNamedPipe((uint) clientHandle.DangerousGetHandle(), 0);
                    //else
                    //    success = ConnectNamedPipe((uint) clientHandle.DangerousGetHandle(), (uint) &no);

                    //could not connect client
                    if (success != 0)
                    {
                        clientse = new Client();
                        clientse.handle = clientHandle;
                        clientse.stream = new FileStream(clientse.handle, FileAccess.ReadWrite, BUFFER_SIZE, false);

                        if (ClientType == 0)
                        {
                            readThread = new Thread(new ThreadStart(Read));
                            readThread.Start();
                        }
                    }
                    else
                    {
                        Thread.Sleep(1000);
                    }
                }
                else
                {
                    Thread.Sleep(1000);
                }
            }
        }
        private void Read()
        {
            //Client client = (Client)clientObj;
            //clientse.stream = new FileStream(clientse.handle, FileAccess.ReadWrite, BUFFER_SIZE, true);
            byte[] buffer = null;
            ASCIIEncoding encoder = new ASCIIEncoding();

            while (true)
            {
                
                int bytesRead = 0;

                try
                {
                    buffer = new byte[BUFFER_SIZE];
                    bytesRead = clientse.stream.Read(buffer, 0, BUFFER_SIZE);
                }
                catch
                {
                    //read error has occurred
                    break;
                }

                //client has disconnected
                if (bytesRead == 0)
                    break;

                //fire message received event
                //if (this.MessageReceived != null)
                //    this.MessageReceived(clientse, encoder.GetString(buffer, 0, bytesRead));

                int ReadLength = 0;
                for (int i = 0; i < BUFFER_SIZE; i++)
                {
                    if (buffer[i].ToString("x2") != "cc")
                    {
                        ReadLength++;
                    }
                    else
                        break;
                }
                if (ReadLength > 0)
                {
                    byte[] Rc = new byte[ReadLength];
                    Buffer.BlockCopy(buffer, 0, Rc, 0, ReadLength);

                    //Console.WriteLine("C# App: Received " + ReadLength +" Bytes: "+ encoder.GetString(Rc, 0, ReadLength));
                    string s = encoder.GetString(Rc, 0, ReadLength);
                    if (!s.Contains("Keep-Alive"))
                    {
                        DataArrived(this, new DataArrivedEventArgs(s));
                    }
                    buffer.Initialize();
                }
               
            }

            //clean up resources
            clientse.stream.Close();
            clientse.handle.Close();
            
        }
        public bool SendMessage(string message, Client client)
        {

                ASCIIEncoding encoder = new ASCIIEncoding();
                byte[] messageBuffer = encoder.GetBytes(message);

                if (client != null)
                {
                    if (client.stream.CanWrite)
                    {
                        client.stream.Write(messageBuffer, 0, messageBuffer.Length);
                        client.stream.Flush();
                    }
                }
                else
                {
                    return false;
                }
                return true;

        }
        public void StopServer()
        {
            //clean up resources

            DisconnectNamedPipe(this.clientHandle);
            
            this.listenThread.Abort();
            if (ClientType == 0)
                this.readThread.Abort();
        }

    }
}
