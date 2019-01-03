// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

using System;
using System.Net;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Microsoft.Azure.SignalR.Samples.Serverless
{
    public class ServerHandler
    {
        private static readonly HttpClient Client = new HttpClient(new LoggingHandler(new HttpClientHandler()));

        private readonly string _serverName;

        private readonly ServiceUtils _serviceUtils;

        private readonly string _hubName;

        private readonly string _endpoint;

        public ServerHandler(string connectionString, string hubName)
        {
            _serverName = GenerateServerName();
            _serviceUtils = new ServiceUtils(connectionString);
            _hubName = hubName;
            _endpoint = _serviceUtils.Endpoint;
        }

        public async Task Start()
        {
            ShowHelp();
            while (true)
            {
                var argLine = Console.ReadLine();
                if (argLine == null)
                {
                    continue;
                }
                var args = argLine.Split(' ');

                if (args.Length == 1 && args[0].Equals("rotate"))
                {
                    Console.WriteLine("Rotating");

                    var request = BuildRequest();
                    var response = await Client.SendAsync(request);

                    if (response.StatusCode != HttpStatusCode.Accepted)
                    {
                        Console.WriteLine($"Sent error: {response.StatusCode}");
                    }
                }
                else
                {
                    Console.WriteLine($"Can't recognize command {argLine}");
                }
            }
        }

        private string GetRotateUrl(string hubName = "rotation")
        {
            return $"{_endpoint}/api/v1/hubs/{hubName.ToLower()}";
        }

        private string GenerateServerName()
        {
            return $"{Environment.MachineName}_{Guid.NewGuid():N}";
        }

        private HttpRequestMessage BuildRequest()
        {
            var url = GetRotateUrl();
            Console.WriteLine(url);
            var request = new HttpRequestMessage(HttpMethod.Post, url);

            request.Headers.Authorization =
                new AuthenticationHeaderValue("Bearer", _serviceUtils.GenerateAccessToken(url, _serverName));
            request.Headers.Accept.Add(new MediaTypeWithQualityHeaderValue("application/json"));
            request.Method = HttpMethod.Post;
            request.Content = new StringContent(JsonConvert.SerializeObject(
                new PayloadMessage
                {
                    target = "rotate",
                    arguments = new object[] {
                        new RotateArguments {
                            X = 0,
                            Y = 0,
                            Z = 0
                        }
                    }
                }
            ), Encoding.UTF8, "application/json");

            return request;
        }

        private void ShowHelp()
        {
            Console.WriteLine("*********Usage*********\n" +
                              "rotate <x> <y> <z>\n" +
                              "***********************");
        }
    }

    public class PayloadMessage
    {
        public string target { get; set; }
        public object[] arguments { get; set; }
    }

    public class RotateArguments
    {
        public int X { get; set; }
        public int Y { get; set; }
        public int Z { get; set; }
    }
}
