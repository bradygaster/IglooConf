using Microsoft.Azure.WebJobs;
using Microsoft.Azure.WebJobs.Host;
using Microsoft.Azure.EventHubs;
using System.Text;
using System.Net.Http;
using Microsoft.Azure.WebJobs.Extensions.SignalRService;
using System.IO;
using Newtonsoft.Json;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;

namespace FunctionApp
{
    public static class MessageReceivedFunction
    {
        private static HttpClient client = new HttpClient();

        [FunctionName("MessageReceivedFunction")]
        [return: Queue("incoming", Connection = "AzureWebJobsStorage")]
        public static async Task<string> RunAsync(
            [EventHubTrigger("iothub-ehub-iglooconf-1138153-c096a88146", 
                Connection = "IoTConnectionString")] EventData message, 
            [SignalR(HubName="climate")] IAsyncCollector<SignalRMessage> messages,
            ILogger log)
        {
            log.LogInformation($"C# IoT Hub trigger function processed a message: " +
            	    "{Encoding.UTF8.GetString(message.Body.Array)}");

            string json = Encoding.UTF8.GetString(message.Body.Array);

            await messages.AddAsync(new SignalRMessage {
                Target = "climateDataReceived",
                Arguments = new [] { json }
            });

            log.LogInformation($"Sent temperature data to SignalR.");

            return json;
        }
    }
}